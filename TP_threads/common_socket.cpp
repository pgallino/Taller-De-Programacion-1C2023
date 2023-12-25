// Copyright [2022] eldipa
// Código tomado de sockets-en-cpp dispuesto por la cátedra

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include "common_socket.h"

#define CONEXIONES_ESPERA 20

Socket::Socket(
        const char *hostname,
        const char *servname) {
    Resolver resolver(hostname, servname, false);

    int s = -1;
    int skt = -1;
    this->closed = true;

    while (resolver.has_next()) {
        struct addrinfo *addr = resolver.next();

        if (skt != -1)
            ::close(skt);

        skt = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (skt == -1) {
            continue;
        }

        s = connect(skt, addr->ai_addr, addr->ai_addrlen);
        if (s == -1) {
            continue;
        }

        this->closed = false;
        this->skt = skt;
        return;
    }

    int saved_errno = errno;

    if (skt != -1)
        ::close(skt);

    throw LibError(
            saved_errno,
            "socket construction failed (connect to %s:%s)",
            (hostname ? hostname : ""),
            (servname ? servname : ""));
}

Socket::Socket(const char *servname) {
    Resolver resolver(nullptr, servname, true);

    int s = -1;
    int skt = -1;
    this->closed = true;
    while (resolver.has_next()) {
        struct addrinfo *addr = resolver.next();

        if (skt != -1)
            ::close(skt);

        skt = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (skt == -1) {
            continue;
        }

        s = bind(skt, addr->ai_addr, addr->ai_addrlen);
        if (s == -1) {
            continue;
        }

        s = listen(skt, CONEXIONES_ESPERA);
        if (s == -1) {
            continue;
        }

        this->closed = false;
        this->skt = skt;
        return;
    }

    int saved_errno = errno;

    if (skt != -1)
        ::close(skt);

    throw LibError(
            saved_errno,
            "socket construction failed (listen on %s)",
            (servname ? servname : ""));
}

Socket::Socket(Socket&& other) {
    this->skt = other.skt;
    this->closed = other.closed;
    other.skt = -1;
    other.closed = true;
}

Socket& Socket::operator=(Socket&& other) {
    if (this == &other)
        return *this;

    if (not this->closed) {
        ::shutdown(this->skt, 2);
        ::close(this->skt);
    }

    this->skt = other.skt;
    this->closed = other.closed;
    other.skt = -1;
    other.closed = true;

    return *this;
}

int Socket::recvsome(
        void *data,
        unsigned int sz,
        bool *was_closed) {
    *was_closed = false;
    int s = recv(this->skt, (char*)data, sz, 0);
    if (s == 0) {
        *was_closed = true;
        return 0;
    } else if (s == -1) {
        throw LibError(errno, "socket recv failed");
    } else {
        return s;
    }
}

int Socket::sendsome(
        const void *data,
        unsigned int sz,
        bool *was_closed) {
    *was_closed = false;

    int s = send(this->skt, (char*)data, sz, MSG_NOSIGNAL);

    if (s == -1) {
        if (errno == EPIPE) {
            *was_closed = true;
            return 0;
        }
        *was_closed = true;
        throw LibError(errno, "socket send failed");
    } else if (s == 0) {
        assert(false);
    } else {
        return s;
    }
}

int Socket::recvall(
        void *data,
        unsigned int sz,
        bool *was_closed) {
    unsigned int received = 0;
    *was_closed = false;

    while (received < sz) {
        int s = recvsome(
                (char*)data + received,
                sz - received,
                was_closed);

        if (s <= 0) {
            assert(s == 0);
            if (received)
                throw LibError(
                        EPIPE,
                        "socket received only %d of %d bytes",
                        received,
                        sz);
            else
                return 0;
        } else {
            received += s;
        }
    }

    return sz;
}

int Socket::sendall(
        const void *data,
        unsigned int sz,
        bool *was_closed) {
    unsigned int sent = 0;
    *was_closed = false;

    while (sent < sz) {
        int s = sendsome(
                (char*)data + sent,
                sz - sent,
                was_closed);

        if (s <= 0) {
            assert(s == 0);
            if (sent)
                throw LibError(
                        EPIPE,
                        "socket sent only %d of %d bytes",
                        sent,
                        sz);
            else
                return 0;
        } else {
            sent += s;
        }
    }

    return sz;
}

Socket::Socket(int skt) {
    this->skt = skt;
    this->closed = false;
}

Socket Socket::accept() {
    int peer_skt = ::accept(this->skt, nullptr, nullptr);
    if (peer_skt == -1)
        throw SktError(errno, "socket accept failed");
    return Socket(peer_skt);
}

void Socket::shutdown(int how) {
    if (::shutdown(this->skt, how) == -1) {
        throw LibError(errno, "socket shutdown failed");
    }
}

int Socket::close() {
    this->closed = true;
    return ::close(this->skt);
}

Socket::~Socket() {
    if (not this->closed) {
        ::shutdown(this->skt, 2);
        ::close(this->skt);
    }
}
