import React, {useState, useEffect} from 'react'
import { Card, CardTitle, CardText } from 'react-toolbox/lib/card'
import Button from 'react-toolbox/lib/button'
import PointInput from '../Input/PointInput'
import { useAppSelector, useAppDispatch } from '../../../../utils/hook'
import { validateValue } from '../../../../utils/validators/PointValidation'
import { setInput } from './UpdatePointInputSlice'
import { PointInputState } from '../PointForm/PointInputSlice'


const UpdateForm = ({inputState, onUpdateHandle}) => {
  
  const [coords, setCoords] = useState<PointInputState>({
    x: inputState.x,
    y: inputState.y,
    r: inputState.r,
    error_x: '',
    error_y: '',
    error_r: ''
  })
  const [isValid, setValid] = useState(false)
  useEffect( () =>{
    setValid(validateValue(coords.r, 'r') && validateValue(coords.y, 'y') && validateValue(coords.x, 'x'))
  }, [coords])

  const handleOnChange = (name: 'x' | 'y' | 'r', value: string) => {
    let error_name = `error_${name}`
    if(validateValue(value, name)){
      setCoords({...coords, [name]: value, [error_name]: ''})
    }
    else{
      setCoords({...coords, [name]: value,[error_name]: 'Invalid value'})
    }
  }

  return (
    <section>
      <Card style={{width: '10 rem'}}>
        <CardTitle title='Coordinates'/>
        <CardText>
          <PointInput
            coord= 'x [-5,3]'
            value={coords.x}
            onChange={(e) => handleOnChange('x', e)}
            error = {coords.error_x}
          />
          <PointInput
            coord= 'y [-3,3]'
            value={coords.y}
            onChange={(e) => handleOnChange('y', e)}
            error = {coords.error_y}
          />
          <PointInput
            coord= 'r [-5,3]'
            value={coords.r}
            onChange={(e) => handleOnChange('r', e)}
            error = {coords.error_r}
          />
          <Button icon='login' label='Update' onClick={() => onUpdateHandle(coords)} raised primary disabled={!isValid} />
        </CardText>
      </Card>
    </section>
  )
}
export default UpdateForm