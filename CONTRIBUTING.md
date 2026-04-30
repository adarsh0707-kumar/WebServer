# Contributing to WebServer

Thank you for considering contributing to the WebServer project! This document provides guidelines and instructions for contributing.

## Code of Conduct

Be respectful and constructive in all interactions. We welcome contributions from everyone.

## Getting Started

1. **Fork the repository** on GitHub
2. **Clone your fork** locally:
   ```bash
   git clone https://github.com/YOUR_USERNAME/WebServer.git
   cd WebServer
   ```
3. **Create a feature branch**:
   ```bash
   git checkout -b feature/your-feature-name
   ```

## Development Workflow

### Building the Project

```bash
make clean
make
```

### Running Tests

```bash
./server &
curl http://localhost:8080/
curl http://localhost:8080/about
kill %1
```

### Code Style Guidelines

- **Indentation**: 4 spaces
- **Naming Conventions**:
  - Classes: `PascalCase` (e.g., `ThreadPool`)
  - Functions: `snake_case` (e.g., `handle_client`)
  - Constants: `UPPER_CASE` (e.g., `BUFFER_SIZE`)
  - Variables: `snake_case` (e.g., `client_socket`)
- **Comments**: Use clear, concise comments for complex logic
- **Line Length**: Preferably under 100 characters

### File Headers

Include this header in new `.cpp` files:

```cpp
/*
 * Filename: description.cpp
 * Author: Your Name
 * Date: YYYY-MM-DD
 * Description: Brief description of the file's purpose
 */
```

## Making Changes

1. **Make your changes** on your feature branch
2. **Write meaningful commit messages**:
   ```bash
   git commit -am "Add feature: description of changes"
   ```
3. **Keep commits atomic**: Each commit should represent one logical change
4. **Test thoroughly** before submitting

## Submitting Changes

1. **Push to your fork**:
   ```bash
   git push origin feature/your-feature-name
   ```
2. **Create a Pull Request** on GitHub with:
   - Clear description of changes
   - Reason for the changes
   - Any related issue numbers
   - Testing instructions if applicable

### Pull Request Guidelines

- Keep PRs focused and reasonably sized
- Link related issues using `Closes #issue_number`
- Provide clear commit history
- Ensure code compiles with `make`
- Test edge cases

## Reporting Bugs

When reporting bugs, include:

1. **Description**: Clear explanation of the bug
2. **Steps to Reproduce**: Exact steps to trigger the bug
3. **Expected Behavior**: What should happen
4. **Actual Behavior**: What actually happened
5. **Environment**: OS, compiler version, C++ standard used
6. **Logs**: Relevant server.log excerpts if applicable

### Bug Report Template

```
**Title**: Brief description of the bug

**Description**:
Detailed description of the bug.

**Steps to Reproduce**:
1. Start server with...
2. Make request to...
3. Observe...

**Expected**: ...
**Actual**: ...

**Environment**:
- OS: (e.g., Ubuntu 20.04)
- Compiler: (e.g., g++ 9.3)
- C++ Standard: (e.g., C++17)
```

## Feature Requests

Feature requests are welcome! Please include:

1. **Use Case**: Why this feature is needed
2. **Description**: How it should work
3. **Examples**: Usage examples or mockups
4. **Implementation Notes**: Any technical thoughts

## Testing

Before submitting, test with:

```bash
# Build clean
make clean && make

# Run server
./server &
SERVER_PID=$!

# Test basic requests
curl http://localhost:8080/
curl http://localhost:8080/about
curl http://localhost:8080/nonexistent

# Load testing
for i in {1..50}; do curl http://localhost:8080 & done
wait

# Cleanup
kill $SERVER_PID
```

## Documentation

When adding features, update:

- `README.md` if user-facing
- `ARCHITECTURE.md` if architectural changes
- Code comments for complex logic
- Commit messages with clear descriptions

## Performance Considerations

- Minimize allocations in hot paths
- Use appropriate data structures
- Profile before optimizing
- Document performance-critical sections

## Security

- Check for buffer overflows
- Validate input properly
- Use safe string handling
- Report security issues privately to maintainers

## Questions?

Feel free to open an issue with the `question` label, or comment on related issues.

## License

By contributing to this project, you agree that your contributions will be licensed under its MIT License.

---

**Thank you for contributing! Your effort helps make WebServer better for everyone.**
