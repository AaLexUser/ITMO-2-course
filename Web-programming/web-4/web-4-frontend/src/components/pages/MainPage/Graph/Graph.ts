import PointResponse from '../../../../types/PointResponse'

export default class Graph{
  private canvas: HTMLCanvasElement
  private ctx:  CanvasRenderingContext2D
  private yMax: any
  private xMax: any

  constructor(canvas: HTMLCanvasElement | null){
    if (canvas){
      this.canvas = canvas
      let ctxNew = canvas.getContext('2d')
      if(ctxNew){
        this.ctx = ctxNew
        this.yMax = canvas.height
        this.xMax = canvas.width
      }
    }
  }
  public getCanvas(){
    return this.canvas
  }

  public draw(){
    this.ctx.fillStyle = '#f1efed'
    this.ctx.fillRect(0,0,this.xMax,this.yMax)
    // draw areas
    this.ctx.fillStyle = '#FF6200'
    this.ctx.beginPath()
    // go center
    this.ctx.moveTo(this.xMax / 2, this.yMax / 2)
    // draw triangle
    this.ctx.lineTo(5 / 6 * this.xMax, this.yMax / 2)
    this.ctx.lineTo(this.xMax / 2,  (5 / 6 * this.yMax))
    this.ctx.lineTo(this.xMax / 2, this.yMax / 2)
    this.ctx.fill()
    this.ctx.beginPath()
    // draw circle
    this.ctx.arc(this.xMax / 2, this.yMax / 2, 1 / 6 * this.xMax, 3 / 2 * Math.PI, Math.PI/2, false)
    this.ctx.fill()
    // draw rectangle
    this.ctx.fillRect(this.xMax / 2, this.yMax / 2,  - 1 / 6 * this.xMax, 2 / 6 * this.yMax)
    // draw grid
    this.ctx.beginPath()
    this.ctx.strokeStyle = 'black'
    for (let i = 1; i < 6; i++) {
      this.ctx.moveTo(this.xMax / 2 - (1 / 60 * this.xMax), i / 6 * this.yMax)
      this.ctx.lineTo(this.xMax / 2 + (1 / 60 * this.xMax), i / 6 * this.yMax)
      this.ctx.moveTo(i / 6 * this.xMax, this.yMax / 2 - (1 / 60 * this.yMax))
      this.ctx.lineTo(i / 6 * this.xMax, this.yMax / 2 + (1 / 60 * this.yMax))
    }
    // draw arrows
    this.ctx.moveTo(0, this.yMax / 2)
    this.ctx.lineTo(this.xMax, this.yMax / 2)
    this.ctx.lineTo(this.xMax - (1 / 60 * this.xMax), this.yMax / 2 - (1 / 60 * this.yMax))
    this.ctx.moveTo(this.xMax, this.yMax / 2)
    this.ctx.lineTo(this.xMax - (1 / 60 * this.xMax), this.yMax / 2 + (1 / 60 * this.yMax))
    this.ctx.moveTo(this.xMax / 2, 0)
    this.ctx.lineTo(this.xMax / 2, this.yMax)
    this.ctx.moveTo(this.xMax / 2, 0)
    this.ctx.lineTo(this.xMax / 2 - (1 / 60 * this.xMax), (1 / 60 * this.yMax))
    this.ctx.moveTo(this.xMax / 2, 0)
    this.ctx.lineTo(this.xMax / 2 + (1 / 60 * this.xMax), (1 / 60 * this.yMax))
    this.ctx.stroke()

    //draw labels
    this.ctx.fillStyle = 'black'
    this.ctx.font = (4 / 60 * this.xMax) + 'px serif'
    this.ctx.fillText('R/2', 4 / 6 * this.xMax - (2 / 60 * this.xMax), this.yMax / 2 - (2 / 60 * this.yMax))
    this.ctx.fillText('R', 5 / 6 * this.xMax - (1 / 60 * this.xMax), this.yMax / 2 - (2 / 60 * this.yMax))
    this.ctx.fillText('-R/2', 2 / 6 * this.xMax - (4 / 60 * this.xMax), this.yMax / 2 - (2 / 60 * this.yMax))
    this.ctx.fillText('-R', 1 / 6 * this.xMax - (this.xMax / 20), this.yMax / 2 - (2 / 60 * this.yMax))

    this.ctx.fillText('-R/2', 2 / 6 * this.xMax + (2 / 60 * this.xMax), 4 / 6 * this.yMax + (1 / 60 * this.yMax))
    this.ctx.fillText('-R', 2 / 6 * this.xMax + (2 / 60 * this.xMax), 5 / 6 * this.yMax + (1 / 60 * this.yMax))
    this.ctx.fillText('R/2', 2 / 6 * this.xMax + (2 / 60 * this.xMax), 2 / 6 * this.yMax + (1 / 60 * this.yMax))
    this.ctx.fillText('R', 2 / 6 * this.xMax + (2 / 60 * this.xMax), 1 / 6 * this.yMax + (1 / 60 * this.yMax))

    //draw axes labels
    this.ctx.font = (4 / 60 * this.xMax) + 'px serif'
    this.ctx.fillText('x', this.xMax - (2 / 60 * this.xMax), this.yMax / 2 + (4 / 60 * this.yMax))
    this.ctx.fillText('y', this.xMax / 2 - (4 / 60 * this.xMax), (2 / 60 * this.yMax))
  }
  drawPoint(point: PointResponse){
    this.ctx.fillStyle = point.hitResult === true ? '#0A8059' : '#ff0404'
    this.ctx.beginPath()
    let scaleX = (1/3*this.xMax*point.x/point.r)+ (this.xMax/2)
    let scaleY = (-1/3*this.yMax*point.y/point.r)+ (this.yMax/2)
    this.ctx.arc(scaleX, scaleY, 5, 0, 2 * Math.PI)
    this.ctx.fill()
  }

  getMousePosition(e) {
    const rect = this.canvas.getBoundingClientRect()
    let mouseX = e.clientX - rect.left | 0
    let mouseY = e.clientY - rect.top | 0
    return {x: mouseX, y: mouseY}
  }
}