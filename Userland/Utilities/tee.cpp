/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/Vector.h>
#include <LibCore/ArgsParser.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

static Vector<int> collect_fds(Vector<const char*> paths, bool append, bool* err)
{
    int oflag;
    mode_t mode;
    if (append) {
        oflag = O_APPEND;
        mode = 0;
    } else {
        oflag = O_CREAT | O_WRONLY | O_TRUNC;
        mode = S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP | S_IRUSR | S_IWUSR;
    }

    Vector<int> fds;
    for (const char* path : paths) {
        int fd = open(path, oflag, mode);
        if (fd < 0) {
            perror("failed to open file for writing");
            *err = true;
        } else {
            fds.append(fd);
        }
    }
    fds.append(STDOUT_FILENO);
    return fds;
}

static void copy_stdin(Vector<int>& fds, bool* err)
{
    for (;;) {
        char buf[4096];
        ssize_t nread = read(STDIN_FILENO, buf, sizeof(buf));
        if (nread == 0)
            break;
        if (nread < 0) {
            perror("read() error");
            *err = true;
            // a failure to read from stdin should lead to an early exit
            return;
        }

        Vector<int> broken_fds;
        for (size_t i = 0; i < fds.size(); ++i) {
            auto fd = fds.at(i);
            int twrite = 0;
            while (twrite != nread) {
                ssize_t nwrite = write(fd, buf + twrite, nread - twrite);
                if (nwrite < 0) {
                    if (errno == EINTR) {
                        continue;
                    } else {
                        perror("write() failed");
                        *err = true;
                        broken_fds.append(fd);
                        // write failures to a successfully opened fd shall
                        // prevent further writes, but shall not block writes
                        // to the other open fds
                        break;
                    }
                } else {
                    twrite += nwrite;
                }
            }
        }

        // remove any fds which we can no longer write to for subsequent copies
        for (auto to_remove : broken_fds)
            fds.remove_first_matching([&](int fd) { return to_remove == fd; });
    }
}

static void close_fds(Vector<int>& fds)
{
    for (int fd : fds) {
        int closed = close(fd);
        if (closed < 0) {
            perror("failed to close output file");
        }
    }
}

static void int_handler(int)
{
    // pass
}

ErrorOr<int> serenity_main(Main::Arguments arguments)
{
    bool append = false;
    bool ignore_interrupts = false;
    Vector<const char*> paths;

    Core::ArgsParser args_parser;
    args_parser.add_option(append, "Append, don't overwrite", "append", 'a');
    args_parser.add_option(ignore_interrupts, "Ignore SIGINT", "ignore-interrupts", 'i');
    args_parser.add_positional_argument(paths, "Files to copy stdin to", "file", Core::ArgsParser::Required::No);
    args_parser.parse(arguments);

    if (ignore_interrupts) {
        if (signal(SIGINT, int_handler) == SIG_ERR)
            perror("failed to install SIGINT handler");
    }

    bool err_open = false;
    bool err_write = false;
    auto fds = collect_fds(paths, append, &err_open);
    copy_stdin(fds, &err_write);
    close_fds(fds);

    return (err_open || err_write) ? 1 : 0;
}
