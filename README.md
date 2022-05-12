# Chimp
*Chimp is a modern parser*. It is a header only c++17 library for parsing command line arguments.
It is heavily inspired by Rust's great library [clap](https://crates.io/crates/clap).

Parts of this document should be treated as a road map for the future rather than description of
current state of the project (until version 1.0 will be released).

# Principia
This library was designed to be *correct*, *beautiful* and *efficient*. Order of those properties
is not accidental. Following subsections consists of their interpretation.

## Correct
Program correctness is a single most important thing. As Joe Armstrong said one of seven deadly sins is

> Code that is very very fast very very **very obscure** and incorrect

This library is designed to enforce correctness. For example there are no throwing around raw pointers,
but rather they are wrapped in `std::shared_ptr`. Errors are reported rather earlier then later.

On the other hand parsing is often only half of a job and parsed data must be validated.
This library exposes API allowing users to specify their constraints that will be
checked during parsing phase. 

## Beautiful
Another deadly sin pointed out by Joe Armstrong is

> Code that is **not beautiful**

For a software to be pleasant to use and to help their users to use it *correctly* it must be beautiful.
This trait is manifested in couple ways in this project.

**Simplicity**. Only things that are simple can be beautiful. This means that there is no deep inheritance or
many different classes. No automatic conversions. No default values unless specifically stated.

**Builder pattern**. One of the ways to accomplish beautiful code is to use builder pattern. This library
encourages that, as it is easier to read and understand (even not knowing it previously) than calling constructors
with 10 arguments.

**Great documentation**. For a code to be beautiful it must have a great documentation with many examples.
It allows for new users and contributors to quickly catch up and maintainers to don't loose control over project.

## Efficient
This library is rather efficient than fast. Normal programs spend a neglectable amount of time parsing
their command line arguments[citation needed]. Therefore hyper-optimising it's speed is mostly irrelevant
(and can potentially lead to obscure and non-beautiful code). This library rather tries to be efficient.
For instance it does not copy around data when it does not need to.

# Parsing logic
This parsing library creates following CLI for user

```
program [SUBCOMMAND] [optional arguments] (required arguments) (positional arguments)
```

When at least one subcommand is present (as an option) it is required. It is treated as a separate program with
it's own parsing rules and can therefore contain another subcommand (like `git remote add`).

Arguments can be optional and required. They have a `--long-name` and can have a short one character name (like `-n`).
Arguments with short names can be concatenated (like in `grep -rnI`). They can take values and be repeated
(if they are declared as such). They can be in any relative position. The only exception to this rule is
their relative position to a subcommand.

Positional arguments do not have names, they are just values (like in `cp source dest`).
They are differentiated based on their relative position with each other.

# SemVer guarantees
For versions `0.x` this project will be in an early development stage. That means that minor version changes
can be backwards incompatible as the API will evolve.

Releasing version `1.0` will mark first stable version of this library. Since then major versions are guaranteed
to be compatible. During development used standard of c++ will be c++17. Version `1.0` will *probably* be using
the same standard. Next major versions might however use newer standards.

# Contributing
All contributions are highly welcome! You can just use this library and send me feedback or report bugs,
pitch ideas and contribute patches. Feel free to open issues and send pull requests.
