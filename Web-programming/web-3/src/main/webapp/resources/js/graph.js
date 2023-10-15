export class Graph {
    canvas;
    ctx;
    yMax;
    xMax;

    constructor(canvas) {
        this.canvas = canvas;
        this.ctx = canvas.getContext("2d");
        this.yMax = canvas.height;
        this.xMax = canvas.width;
    }

    draw() {
        // draw areas
        this.ctx.fillStyle = '#FF6200'
        this.ctx.beginPath();
        // go center
        this.ctx.moveTo(this.xMax / 2, this.yMax / 2);
        // draw triangle
        this.ctx.lineTo(5 / 6 * this.xMax, this.yMax / 2);
        this.ctx.lineTo(this.xMax / 2, 1 / 6 * this.yMax);
        this.ctx.lineTo(this.xMax / 2, this.yMax / 2);
        this.ctx.fill();
        this.ctx.beginPath();
        // draw circle
        this.ctx.arc(this.xMax / 2, this.yMax / 2, 1 / 6 * this.xMax, Math.PI, 0, false);
        this.ctx.fill();
        // draw rectangle
        this.ctx.fillRect(this.xMax / 2, this.yMax / 2, 1 / 6 * this.xMax, 2 / 6 * this.yMax);

        // draw grid
        this.ctx.beginPath();
        this.ctx.strokeStyle = 'black';
        for (let i = 1; i < 6; i++) {
            this.ctx.moveTo(this.xMax / 2 - (1 / 60 * this.xMax), i / 6 * this.yMax);
            this.ctx.lineTo(this.xMax / 2 + (1 / 60 * this.xMax), i / 6 * this.yMax);
            this.ctx.moveTo(i / 6 * this.xMax, this.yMax / 2 - (1 / 60 * this.yMax));
            this.ctx.lineTo(i / 6 * this.xMax, this.yMax / 2 + (1 / 60 * this.yMax));
        }
        // draw arrows
        this.ctx.moveTo(0, this.yMax / 2);
        this.ctx.lineTo(this.xMax, this.yMax / 2);
        this.ctx.lineTo(this.xMax - (1 / 60 * this.xMax), this.yMax / 2 - (1 / 60 * this.yMax));
        this.ctx.moveTo(this.xMax, this.yMax / 2);
        this.ctx.lineTo(this.xMax - (1 / 60 * this.xMax), this.yMax / 2 + (1 / 60 * this.yMax));
        this.ctx.moveTo(this.xMax / 2, 0);
        this.ctx.lineTo(this.xMax / 2, this.yMax);
        this.ctx.moveTo(this.xMax / 2, 0);
        this.ctx.lineTo(this.xMax / 2 - (1 / 60 * this.xMax), (1 / 60 * this.yMax));
        this.ctx.moveTo(this.xMax / 2, 0);
        this.ctx.lineTo(this.xMax / 2 + (1 / 60 * this.xMax), (1 / 60 * this.yMax));
        this.ctx.stroke();

        //draw labels
        this.ctx.fillStyle = 'black';
        this.ctx.font = (4 / 60 * this.xMax) + 'px serif';
        this.ctx.fillText('R/2', 4 / 6 * this.xMax - (2 / 60 * this.xMax), this.yMax / 2 - (2 / 60 * this.yMax));
        this.ctx.fillText('R', 5 / 6 * this.xMax - (1 / 60 * this.xMax), this.yMax / 2 - (2 / 60 * this.yMax));
        this.ctx.fillText('-R/2', 2 / 6 * this.xMax - (4 / 60 * this.xMax), this.yMax / 2 - (2 / 60 * this.yMax));
        this.ctx.fillText('-R', 1 / 6 * this.xMax - (this.xMax / 20), this.yMax / 2 - (2 / 60 * this.yMax));

        this.ctx.fillText('-R/2', 2 / 6 * this.xMax + (2 / 60 * this.xMax), 4 / 6 * this.yMax + (1 / 60 * this.yMax));
        this.ctx.fillText('-R', 2 / 6 * this.xMax + (2 / 60 * this.xMax), 5 / 6 * this.yMax + (1 / 60 * this.yMax));
        this.ctx.fillText('R/2', 2 / 6 * this.xMax + (2 / 60 * this.xMax), 2 / 6 * this.yMax + (1 / 60 * this.yMax));
        this.ctx.fillText('R', 2 / 6 * this.xMax + (2 / 60 * this.xMax), 1 / 6 * this.yMax + (1 / 60 * this.yMax));

        //draw axes labels
        this.ctx.font = (4 / 60 * this.xMax) + 'px serif';
        this.ctx.fillText('x', this.xMax - (2 / 60 * this.xMax), this.yMax / 2 + (4 / 60 * this.yMax));
        this.ctx.fillText('y', this.xMax / 2 - (4 / 60 * this.xMax), (2 / 60 * this.yMax));
    }
    drawPoint(x,y,r, isHit){
        this.ctx.fillStyle = isHit ? '#0A8059' : '#ff0404'
        this.ctx.beginPath();
        let scaleX = (1/3*this.xMax*x/r)+ (this.xMax/2);
        let scaleY = (-1/3*this.yMax*y/r)+ (this.yMax/2);
        this.ctx.arc(scaleX, scaleY, 5, 0, 2 * Math.PI);
        this.ctx.fill();
    }
    getMousePosition(e) {
        let mouseX = e.offsetX * this.canvas.width / this.canvas.clientWidth | 0;
        let mouseY = e.offsetY * this.canvas.height / this.canvas.clientHeight | 0;
        return {x: mouseX, y: mouseY};
    }
}