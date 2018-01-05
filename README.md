## Gordian

Gordian is a simple combination generator based on the phoenix password generator.

## Installation

Simply compile the source code using the command:

```
gcc *.c -o prog_name

```

## Usage

To generate combinations all you have to do is specify length, characters, and file name.

```
prog_name 6 0-9 file.txt
```

You can either specify individual characters as in 0123456789, or use ranges a-z 0-9 A-Z.

## Options

This program comes with 6 available options:

	-p when used the results are printed to screen, to be used for piping operation.
	-a all possible combinations of the characters specified will be generated, if no option is given -a is implied.
	-m only combinations that have at least two matching characters will be generated, i.e 0112
	-u only combinations that don't contain matching characters will be generated, i.e 0121
	-s only combinations that contain different characters on each position will be generated, i.e 0123
	-b the pattern that follows will be added to the beginning of the combinations being generated e.g -n 12 then 12***

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/spirosavlonitis/gordian. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [Contributor Covenant](http://contributor-covenant.org) code of conduct.


## License

The program is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).

