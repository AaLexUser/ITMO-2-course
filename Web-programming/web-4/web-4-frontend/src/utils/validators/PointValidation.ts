const RANGES = {x: [-5,3], y: [-3,3], r: [-5,3]}
export const validateValue = (value: string, rangeKey: 'x' | 'y' | 'r') => {
  return validateDouble(value) && validateRange(+value, RANGES[rangeKey][0], RANGES[rangeKey][1])
}

const validateDouble = (value: string): boolean => {
  const pattern: RegExp =  /^[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?$/
  return pattern.test(value)
}

const validateRange = (value: number, min: number, max: number): boolean => {
  return value >= min && value <= max
}