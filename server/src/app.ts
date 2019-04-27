import express from 'express';
import winston from 'winston';
import expressWinston from 'express-winston';
import io from 'socket.io';
import http from 'http';
import path from 'path';

const app = express();
const port = 3001;

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

const socketIo = io(server);

socketIo.on('connection', (socket) => {
    socket.emit('news', {hello: 'world'});

    socket.on('color', (data) => {
        console.log(data);
        let [r, g, b] = data['color'].replace('rgb(', '').replace(')', '').split(',').map((it: string) => parseInt(it));
        
        socketIo.emit('colorInput', {r, g, b});
    });

    socket.on('path', (data) => {
        console.log(data);
        socketIo.emit('pathInput', data);
    });

    socket.on('stroke', (data) => {
        console.log(data);
        socketIo.emit("strokeInput", data);
    });

    socket.on('clear', (data) => {
        console.log(data);
        socketIo.emit('clearInput', data);
    });

    socket.on('disconnect', (reason) => {
        console.log(socket.id);
    });
});


app.get('/', (req, res) => {
    res.sendFile( path.join(__dirname.replace('src', ''), 'public/index.html') );
});
