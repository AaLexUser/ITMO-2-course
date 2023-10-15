export function drawGraph(){
    // draw areas
    var canvas = document.getElementById("graph");
    var ctx = canvas.getContext("2d");
    ctx.beginPath();
    ctx.moveTo(150,50);
    ctx.lineTo(50,150);
    ctx.lineTo(150,150);
    ctx.lineTo(150,50);
    ctx.fillStyle = '#02a5ae';
    ctx.fill();
    ctx.beginPath();
    ctx.arc(150, 150, 100, Math.PI, 0 , true);
    ctx.fill();
    ctx.fillRect(50,150,100,100);
    
    //draw grid
    ctx.beginPath();
    ctx.strokeStyle = 'white';
    ctx.moveTo(150, 300);
    ctx.lineTo(150, 0)
    ctx.lineTo(145,10);
    ctx.moveTo(150,0);
    ctx.lineTo(155,10);
    ctx.moveTo(145,50);
    ctx.lineTo(155,50);
    ctx.moveTo(145,100);
    ctx.lineTo(155,100);
    ctx.moveTo(145,200);
    ctx.lineTo(155,200);
    ctx.moveTo(145,250);
    ctx.lineTo(155,250);
    ctx.moveTo(0,150);
    ctx.lineTo(300,150);
    ctx.moveTo(300,150);
    ctx.lineTo(290,145);
    ctx.moveTo(300,150);
    ctx.lineTo(290,155);
    ctx.moveTo(250,145);
    ctx.lineTo(250,155);
    ctx.moveTo(200,145);
    ctx.lineTo(200,155);
    ctx.moveTo(100,145);
    ctx.lineTo(100,155);
    ctx.moveTo(50,145);
    ctx.lineTo(50,155);
    ctx.stroke();

    //draw labels
    ctx.fillStyle = 'white';
    ctx.font = '20px serif';
    ctx.fillText('R/2', 190, 140);
    ctx.fillText('R', 245, 140);
    ctx.fillText('-R/2', 80, 140);
    ctx.fillText('-R', 35, 140);

    ctx.fillText('-R/2', 160, 205);
    ctx.fillText('-R', 160, 255);
    ctx.fillText('R/2', 160, 105);
    ctx.fillText('R', 160, 55);

}
export function drawPoint(x=150,y=150,r=2){

    drawGraph();

    var canvas = document.getElementById("graph");
    var ctx = canvas.getContext("2d");

    ctx.beginPath();
    ctx.fillStyle = '#d50000';
    ctx.arc(x, y, 5, 0, 2 * Math.PI);
    ctx.fill();
}