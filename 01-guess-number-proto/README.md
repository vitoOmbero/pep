# behold the prototype

## what

Simple text based "guess the number" game in one file.

## what is wrong

- text based game and text based engine in one binary file,   
- application, which provides execution context, is "inlined" too, 
- text view service implementation is bounded to stdout,
- no simple way for new features integration: no OOP, no modular code, no domain model (even nothing insinuates)


