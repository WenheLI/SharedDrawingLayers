let colors = [];
let colorIndex = 0;
let eraser = false;
let isClear = false;
let strokeValue = 6;

let socket = io.connect('http://localhost:3001');

// window.onresize = (e) => {
//     resizeCanvas(e.target.width * 0.8,  e.target.height);
// }

function setup() {
    let canvas = createCanvas(640, 480);
    canvas.parent('canvas');
    
    let colorButtons = Array.from(document.querySelectorAll('#color-panel div'));

    colors = colorButtons.map((ele) => {
        ele.addEventListener('click', () => {
            colorIndex = ele.dataset.index;
            colorButtons.forEach((button) => button.className = '');
            ele.className = 'selected';
            socket.emit('color', {color: colors[colorIndex]});
        });
        return window.getComputedStyle(ele).backgroundColor
    });

    socket.emit('color', {color: colors[0]});

    document.getElementById('eraser').addEventListener('click', () => {
        eraser = !eraser;
        socket.emit('eraser', {eraser});
    });

    document.getElementById('clear').addEventListener('click', () => {
        isClear = true;
        socket.emit('clear', {isClear});
    });

    document.getElementById('stroke').addEventListener('input', (tar) => {
        strokeValue = parseInt(tar.currentTarget.value);
        socket.emit('stroke', {stroke: strokeValue});
    });

    document.getElementById('export').addEventListener('click', () => {
        document.getElementsByTagName('canvas')[0].toBlob((b) => {
            let downloadLink = document.createElement('a');
            downloadLink.href = URL.createObjectURL(b);
            downloadLink.download = "export.jpg";
            document.body.appendChild(downloadLink);
            downloadLink.click();
            let tempTimer = setTimeout(() => {
                document.body.removeChild(downloadLink)
                clearTimeout(tempTimer);
            }, 100);
        })
    });

}

function draw() {
    if (isClear) {
        background(255);
        isClear = false;
    }

}

function mouseDragged() {
    push();
        noStroke();
        fill(eraser ? 255 : colors[colorIndex])
        ellipse(mouseX, mouseY, strokeValue, strokeValue);
    pop();
    
    if (mouseX >= 0 && mouseX <= parseInt(canvas.style.width.split('.')[0]) && 
        mouseY >= 0 && mouseY <= parseInt(canvas.style.height.split('.')[0])) {
            socket.emit('path', {mouseX, mouseY});
    }   
}