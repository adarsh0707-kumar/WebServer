# WebServer

A lightweight multi-threaded HTTP web server written in C++.

## Overview

This project implements a simple static file server using POSIX sockets and a thread pool.
It listens on port `8080`, accepts incoming HTTP connections, and serves files from the `www/` directory.

## Features

- Multi-threaded request handling with a custom thread pool
- Serves static `.html`, `.css`, `.js`, and `.png` files
- Supports `/` mapped to `www/index.html`
- Supports requests to `/page` mapped to `www/page.html`
- Returns a `404 Not Found` page for missing resources
- Simple request logging to `server.log`

## Project Structure

- `src/`
  - `main.cpp` — server startup
  - `server.cpp` — socket creation, bind/listen loop, and connection acceptance
  - `thread_pool.cpp` — worker thread pool implementation
  - `http_handler.cpp` — HTTP request parsing and response generation
  - `utils.cpp` — file loading, MIME type detection, and logging
- `inc/`
  - Header files for each component
- `www/`
  - Static content served by the web server
- `Makefile` — build and run commands

## Requirements

- Linux or UNIX-like system
- `g++` with C++17 support
- POSIX threads (`-pthread`)

## Build

```sh
make
```

## Run

```sh
./server
```

The server starts and listens on port `8080`.

## Test

Open a web browser and visit:

- `http://localhost:8080/`
- `http://localhost:8080/about`

Or use `curl`:

```sh
curl http://localhost:8080/
```

## Notes

- Static files are served from the `www/` directory.
- The server currently appends `.html` to requested paths.
- Access to parent directories is blocked by a basic path check.

## Clean

```sh
make clean
```
