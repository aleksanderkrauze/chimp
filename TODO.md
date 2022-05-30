# TODOs

## Now

- Fix CI. Check why integration tests sometimes fail.
- Split Arg into subclasses
- make all builders functions && ref-qualified

## v0.1

- Do basic implementation of App, Arg, Command and their builders.
- write tests
- write documentation
- create `CHANGELOG.md`
- Add information about theme to the docs footer

## v0.2

- add support for wide strings (or just Unicode codepoints)
- make things `constexpr`
- use templates that use their types to differentiate between their usage
	(is_positional for example)
- Add aliases for Args
- Add support for special `-` and `--` flags
