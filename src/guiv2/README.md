# 5327K's Pure Pursuit GUI

This directory holds the code for the GUI simulation for this Pure Pursuit implementation. Under the hood, it uses `websocketpp` to communicate with a `React.js` webserver.

## Websocket API

Each message from the client (the website) should send messages in this form:
```
{message-type}
{data}
```

Where `{message-type}` is a single "word" (without any spaces or whitespace inside of it, e.g. by replacing spaces with dashes), and the remaining part is the `{data}` to be consumed by the server.

In return, the server will repond either:
```
ERROR
{message}
```
Which indicates an error occurred outside of a specific handler, or
```
ERROR {message-type}
{message}
```
Which indicates an error occured during the handling of that specific type of event, or
```
SUCCESS {message-type}
{data}
```
Which indicates that the handler succesfully processed the message and returned some data.


