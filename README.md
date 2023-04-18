# Minishell

Welcome to Minishell, a simple shell implementation designed to provide basic shell functionality.

## Getting Started

To get started with Minishell, simply clone the repository and follow the build instructions below.

```bash
git clone https://github.com/yuki-shimoda-crypto/42_minishell.git
cd 42_minishell
```

## Build Instructions

To build Minishell, follow these steps:

1. Install the necessary dependencies:
    - For Ubuntu/Debian-based systems:
        ```bash
        sudo apt install build-essential
        ```
    - For macOS:
        ```bash
        xcode-select --install
        ```
2. Run the build script:
    ```bash
    ./make
    ```
3. Start Minishell:
    ```bash
    ./minishell
    ```

## Contributing

We welcome contributions to Minishell!

Please read our [CONTRIBUTING.md](./CONTRIBUTING.md) for guidelines on branch naming and commit messages.

### Branch Naming Guidelines

Please use the following template for your branch names:

`<category>`/`<issue-number>`-`<short-description>`

`<category>` should be one of the following:

- `feature`: For new features or functionality additions.
- `fix`: For bug fixes.
- `docs`: For documentation changes.
- `style`: For code style adjustments (indentation, whitespace, etc.) without logic changes.
- `refactor`: For code refactoring without adding new features or fixing bugs.
- `test`: For addition or modification of test code.
- `chore`: For build process or tooling changes.

`<issue-number>` should be the issue number that your branch is addressing (e.g., 123).

`<short-description>` should be a few words describing the purpose of the branch, using hyphens to separate words (e.g., add-login-feature).

Example:

feature/123-add-login-feature

### Commit Message Guidelines

`<type>`(`<scope>`): `<Short description>` (less than 50 characters)

Commit type: (Choose one of the following)

- `feature`: A new feature or functionality addition
- `fix`: A bug fix
- `docs`: Documentation changes
- `style`: Code style adjustments (indentation, whitespace, etc.) without logic changes
- `refactor`: Code refactoring without adding new features or fixing bugs
- `test`: Addition or modification of test code
- `chore`: Build process or tooling changes

Scope: (A brief description of the part of the codebase affected by the commit)

Long description (wrap at 72 characters):
- More detailed explanation of what the commit does.
- You can use multiple bullet points if needed.

Motivation:
- Explain the motivation behind the changes in this commit.

Issue or Pull Request: (e.g., "Issue: #123" or "PR: #456")
- If applicable, add a reference to the issue or pull request that this commit addresses.

## License

This project is licensed under the MIT License.
