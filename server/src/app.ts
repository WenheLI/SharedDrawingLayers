import express from 'express';
import winston from 'winston';
import expressWinston from 'express-winston';
import io from 'socket.io';
import http from 'http';
import path from 'path';

const app = express();
const port = 3000;

const server = new http.Server(app);
server.listen(port)

app.use(expressWinston.logger({
    transports: [new winston.transports.Console()],
    expressFormat: true,
    meta: true,
    colorize: true,
    ignoreRoute: function (req, res) { return false; },
    msg: "HTTP {{req.method}} {{req.url}}"
}));

app.use(express.static(path.join(__dirname.replace('src', ''), 'public')))

const socket = io(server);

socket.on('connection', (socket) => {
    socket.emit('news', {hello: 'world'}),
    socket.on('color', (data) => {
        console.log(data);
    });

    socket.on('path', (data) => {
        console.log(data);
    });

    socket.on('disconnect', (reason) => {
        console.log(socket.id);
    });
});


app.get('/', (req, res) => {
    res.sendFile( path.join(__dirname.replace('src', ''), 'public/index.html') );
});