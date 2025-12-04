# <img src="https://github.com/user-attachments/assets/de0ad8c8-077d-4f28-95eb-6d4f26378751" alt="mempass logo" width="20" /> mempass

Securely practice typing out your secrets.

> [!IMPORTANT]
> Work in progress; not working yet.

## What is it? ❓

If you have a long password that you'd like to remember, you can practice typing it out using mempass, a simple pure C CLI program that helps you do just that.

## Security 🔐

* The terminal does not echo the password back (using [`termios(3)`](https://linux.die.net/man/3/termios)).
* Custom implementation of a `shred()` function that uses `/dev/urandom` to overwrite the secret string data a hundred times.
* (TODO) Hashing.
* (TODO) Non exploitable string comparison (always O(n) with a flag that is being ORed with A's and B's bits).
* (TODO) Storage of secrets using a file? (Where? What format? Hashed? Salted, peppered & allat?)

## Acknowledgements 🙏

* The beautiful [`man(1)`](https://linux.die.net/man/) pages.
* Inspiration from [Mister Zozin](https://www.youtube.com/tsoding) (because he is a wizard (to me)).

## Motivation 💡

I wanted to practice my C and securely remember my password.
