# WebServer

A lightweight, multi-threaded HTTP web server written in C++17. Designed for serving static content with efficient request handling using a thread pool architecture.

**Status:** ✓ Production Ready | **License:** MIT | **C++ Standard:** C++17

## 🚀 Features

- **Multi-threaded Architecture**: Configurable thread pool for concurrent request handling
- **HTTP/1.1 Support**: Full HTTP/1.1 request parsing and response generation
- **Static File Serving**: Serves HTML, CSS, JavaScript, PNG, and other static content
- **Content-Type Detection**: Automatic MIME type detection based on file extension
- **Path Security**: Built-in protection against directory traversal attacks (`../` detection)
- **Logging**: Structured logging to `server.log` with timestamps
- **Memory Safe**: Proper resource cleanup and error handling
- **Performance**: Efficient socket I/O and buffer management

## 📋 Requirements

- **OS**: Linux, macOS, or other UNIX-like systems
- **Compiler**: `g++` 9.0+ with C++17 support
- **Build Tool**: `make`
- **Dependencies**: POSIX threads (included in standard library)

## 🔧 Build

```bash
make              # Build the project
make clean        # Remove build artifacts
make run          # Build and run the server
```

## 🎯 Usage

### Quick Start

```bash
./server
```

Server will start on `http://localhost:8080`

### Accessing Content

```bash
# Index page
curl http://localhost:8080/

# Specific page (maps to www/about.html)
curl http://localhost:8080/about

# Multiple concurrent requests
for i in {1..10}; do curl http://localhost:8080 & done
```

### Configuration

Edit `src/main.cpp` to adjust:

- **Port**: Line 5 (`int port = 8080;`)
- **Thread Count**: Line 6 (`int threads = 4;`)

## 📁 Project Structure

```
.
├── inc/                  # Header files
│   ├── server.h         # Server class interface
│   ├── thread_pool.h    # Thread pool implementation
│   ├── http_handler.h   # HTTP request handler
│   └── utils.h          # Utility functions
├── src/                 # Source files
│   ├── main.cpp         # Server entry point
│   ├── server.cpp       # Server socket implementation
│   ├── thread_pool.cpp  # Thread pool worker logic
│   ├── http_handler.cpp # HTTP request parsing & response
│   └── utils.cpp        # File I/O and logging utilities
├── www/                 # Static content directory
│   ├── index.html       # Homepage
│   └── about.html       # About page
├── Makefile             # Build configuration
├── README.md            # This file
└── .gitignore           # Git ignore rules
```

## 🏗️ Architecture

### Thread Pool Pattern

The server uses a producer-consumer thread pool pattern:

1. **Main Thread**: Accepts incoming connections and enqueues them
2. **Worker Threads**: Dequeue clients and process HTTP requests
3. **Synchronization**: Mutex and condition variables for thread-safe queue

### Request Flow

```
Client Connection → Accept → Enqueue → Worker Thread → Parse HTTP → Load File → Send Response → Close
```

## 📝 HTTP Response Examples

### Success (200 OK)

```
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 256

<html>...</html>
```

### Not Found (404)

```
HTTP/1.1 404 Not Found
Content-Type: text/html
Content-Length: 25

<h1>404 Not Found</h1>
```

## 🔍 Logging

Server logs are written to `server.log` with timestamps:

```
Wed Apr 28 12:34:56 2026: Request: GET /about
Wed Apr 28 12:34:57 2026: New client connected
```

## 🛡️ Security Features

- **Path Traversal Protection**: Rejects requests containing `..` sequences
- **Buffer Overflow Prevention**: Fixed-size buffers with bounds checking
- **Resource Cleanup**: Proper socket and file handle closure

## 📊 Performance Tuning

- Adjust `THREAD_COUNT` in `main.cpp` for your system
- Typical: 4-8 threads for small workloads, scale up for high concurrency
- Buffer size: 30KB for request reading (configurable in `http_handler.cpp`)

## 🤝 Contributing

Contributions welcome! Please:

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/my-feature`
3. Commit changes: `git commit -am 'Add feature'`
4. Push to branch: `git push origin feature/my-feature`
5. Submit a Pull Request

## 📄 License

This project is licensed under the MIT License - see LICENSE file for details.

## 🎓 Learning Resources

This project demonstrates:

- POSIX socket programming
- Multi-threading with std::thread
- HTTP protocol basics
- Thread pool design pattern
- C++17 standard library features

## ⚠️ Limitations

- Single-process architecture (not cluster-aware)
- No HTTPS/TLS support
- Limited HTTP/1.1 features (no chunked encoding, pipelining)
- No caching mechanism
- Static files only

## 🐛 Known Issues

None currently. Please report bugs via GitHub Issues.

## 📞 Support

For questions or support, open an issue on GitHub.

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
