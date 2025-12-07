# <img src="https://github.com/user-attachments/assets/de0ad8c8-077d-4f28-95eb-6d4f26378751" alt="mempass logo" width="20" /> mempass

Securely practice typing out your secrets.

> [!IMPORTANT]
> Work in progress; not working yet.

## What is it? ❓

If you have a long password that you'd like to remember, you can practice typing it out using mempass, a simple pure C CLI program that helps you do just that.

## Usage

W.I.P.

In `./src/main.c` there's a TODO section which contains how I'd like to use mempass.

## Compatibility

Linux: OK (make sure to have openssl-dev for compilation, and openssl for the execution)
MacOS: MAYBE
Windows: NO (We're using termios which isn't on Windows, and surely more things).

## Compiling

*Inside `./src`*

`clang -lcrypto -O2 -o mempass main.c`

(or `gcc`)

## Security 🔐

* The terminal does not echo the password back (using [`termios(3)`](https://linux.die.net/man/3/termios)).  

* Custom implementation of a `shred()` function that uses `/dev/urandom` to overwrite the secret string data a hundred times.  

* Hashing: Sha512 using libssl and salted straight from `/dev/urandom`  

* (TODO) Non exploitable string comparison (always O(n) with a flag that is being ORed with A's and B's bits).  

* (TODO) Storage of secrets using a file? (Where? What format? Hashed? Salted, peppered & allat?)  

## Motivation 💡

I wanted to practice my C and securely remember my password.

A bit of a thought experiment, I used what I know to make the code "secure".  
Usually, some of the techniques that I implement (adequately or not) would be used for
API endpoints and the likes, but I think they're pretty much useless for a short-lived 
program like this one.

It would've been greatly faster, easier and more secure to do it in Rust, but as I said, this is 
an educational project.


## Flaws & Potential Flaws

* I don't know what I'm doing.

* Using a big library (libssl) for such a small software is sad, we're dependent on an external library.

* It's C.

## Acknowledgements 🙏

* The beautiful [`man(1)`](https://linux.die.net/man/) pages.
* Inspiration from [Mister Zozin](https://www.youtube.com/tsoding) (because he is a wizard (to me)).
* StackOverflow, Google & ChatGPT.

