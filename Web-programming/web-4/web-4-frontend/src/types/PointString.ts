interface PointString {
  id?: string | number,
  x: string | number,
  y: string | number, 
  r: string | number,
  hitResult: string | boolean,
  time?: string | Date,
  executionTime?: number | string,
  username?: string
}
export default PointString