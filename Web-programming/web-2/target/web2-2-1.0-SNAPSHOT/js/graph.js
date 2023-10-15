export const canvas = document.getElementById("graph");
const ctx = canvas.getContext("2d");
const yMax = canvas.height;
const xMax = canvas.width;

export function drawGraph(){
    // draw areas
    ctx.beginPath();
    ctx.moveTo(xMax/2,yMax/2);
    ctx.lineTo(2/6*xMax,yMax/2);
    ctx.lineTo(xMax/2,5/6*yMax);
    ctx.lineTo(xMax/2,yMax/2);
    ctx.fillStyle = '#FF6200';
    ctx.fill();
    ctx.beginPath();
    ctx.arc(xMax/2, yMax/2, 2/6*xMax, 3/2*Math.PI, Math.PI/2 , false);
    ctx.fill();
    ctx.fillRect(xMax/2,yMax/2,2/6*xMax,2/6*yMax);

    //draw grid
    ctx.beginPath();
    ctx.strokeStyle = 'black';
    ctx.moveTo(xMax/2, yMax);
    ctx.lineTo(xMax/2, 0)
    ctx.lineTo(xMax/2-(1/60*xMax),2/60*yMax);
    ctx.moveTo(xMax/2,0);
    ctx.lineTo(xMax/2+(1/60*xMax),2/60*yMax);
    ctx.moveTo(xMax/2-(1/60*xMax),1/6*yMax);
    ctx.lineTo(xMax/2+(1/60*xMax),1/6*yMax);
    ctx.moveTo(xMax/2-(1/60*xMax),2/6*yMax);
    ctx.lineTo(xMax/2+(1/60*xMax),2/6*yMax);
    ctx.moveTo(xMax/2-(1/60*xMax),4/6*yMax);
    ctx.lineTo(xMax/2+(1/60*xMax),4/6*yMax);
    ctx.moveTo(xMax/2-(1/60*xMax),5/6*yMax);
    ctx.lineTo(xMax/2+(1/60*xMax),5/6*yMax);
    ctx.moveTo(0,yMax/2);
    ctx.lineTo(xMax,yMax/2);
    ctx.moveTo(xMax,yMax/2);
    ctx.lineTo(xMax-(2/60*xMax),yMax/2-(1/60*yMax));
    ctx.moveTo(xMax,yMax/2);
    ctx.lineTo(xMax-(2/60*xMax),yMax/2+(1/60*yMax));
    ctx.moveTo(5/6*xMax,yMax/2-(1/60*yMax));
    ctx.lineTo(5/6*xMax,yMax/2+(1/60*yMax));
    ctx.moveTo(4/6*xMax,yMax/2-(1/60*yMax));
    ctx.lineTo(4/6*xMax,yMax/2+(1/60*yMax));
    ctx.moveTo(2/6*xMax,yMax/2-(1/60*yMax));
    ctx.lineTo(2/6*xMax,yMax/2+(1/60*yMax));
    ctx.moveTo(1/6*xMax,yMax/2-(1/60*yMax));
    ctx.lineTo(1/6*xMax,yMax/2+(1/60*yMax));
    ctx.stroke();

    //draw labels
    ctx.fillStyle = 'black';
    ctx.font = (4/60*xMax) +'px serif';
    ctx.fillText('R/2', 4/6*xMax-(2/60*xMax), yMax/2-(2/60*yMax));
    ctx.fillText('R', 5/6*xMax-(1/60*xMax), yMax/2-(2/60*yMax));
    ctx.fillText('-R/2', 2/6*xMax-(4/60*xMax), yMax/2-(2/60*yMax));
    ctx.fillText('-R', 1/6*xMax-(xMax/20), yMax/2-(2/60*yMax));

    ctx.fillText('-R/2', 2/6*xMax+(2/60*xMax), 4/6*yMax+(1/60*yMax));
    ctx.fillText('-R', 2/6*xMax+(2/60*xMax), 5/6*yMax+(1/60*yMax));
    ctx.fillText('R/2', 2/6*xMax+(2/60*xMax), 2/6*yMax+(1/60*yMax));
    ctx.fillText('R', 2/6*xMax+(2/60*xMax), 1/6*yMax+(1/60*yMax));

}
export function drawPoint(x,y,r, isHit){
    ctx.fillStyle = isHit ? '#0A8059' : '#ff0404'
    ctx.beginPath();
    let scaleX = (1/3*xMax*x/r)+ (xMax/2);
    let scaleY = (-1/3*yMax*y/r)+ (yMax/2);
    ctx.arc(scaleX, scaleY, 5, 0, 2 * Math.PI);
    ctx.fill();
}
export function getMousePosition(e) {
    let mouseX = e.offsetX * canvas.width / canvas.clientWidth | 0;
    let mouseY = e.offsetY * canvas.height / canvas.clientHeight | 0;
    return {x: mouseX, y: mouseY};
}
