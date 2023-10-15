import React, {useEffect, useState} from 'react'
import { Card, CardTitle, CardText } from 'react-toolbox/lib/card'
import ErrorDialog from '../../../layouts/ErrorDialog'
import Button from 'react-toolbox/lib/button'
import PointInput from '../Input/PointInput'
import { useAppDispatch, useAppSelector } from '../../../../utils/hook'
import { useAddPointMutation } from '../../../../store/slices/PointApi'
import { setInput, resetInput } from './PointInputSlice'
import { validateValue } from '../../../../utils/validators/PointValidation'
const PointForm = () => {
  const pointInput = useAppSelector(state => state.pointInput)
  const dispatch = useAppDispatch()
  const [addPoint, {isLoading}] = useAddPointMutation()
  const token = useAppSelector(state => state.user).user.token
  const [isValid, setValid] = useState(false)
  useEffect( () =>{
    setValid(validateValue(pointInput.r, 'r') && validateValue(pointInput.y, 'y') && validateValue(pointInput.x, 'x'))
  }, [pointInput])
  useEffect(()=> {
  },[isValid])
  const handleOnSubmit = async () =>  {
    await addPoint({token: token, body: ({x: +pointInput.x, y: +pointInput.y, r: +pointInput.r}) }).unwrap()
      .then((response)=>
        dispatch(resetInput())
      )
  }

  const handleOnChange = (name: 'x' | 'y' | 'r', value: string) => {
    let error_name = `error_${name}`
    if(validateValue(value, name)){
      dispatch(setInput({...pointInput, [name]: value, [error_name]: ''}))
    }
    else{
      dispatch(setInput({...pointInput, [name]: value,[error_name]: 'Invalid value'}))
    }
  }
  return (
    <section>
      <Card style={{
        width: '330px',
        height: '390px',
        margin: '0.1rem'
      }}>
        <CardTitle title='Coordinates'/>
        <CardText>
          <PointInput
            coord= 'x [-5,3]'
            value={pointInput.x}
            onChange={(e: string) => handleOnChange('x', e)}
            error = {pointInput.error_x}
          />
          <PointInput
            coord= 'y [-3,3]'
            value={pointInput.y}
            onChange={(e) => handleOnChange('y', e)}
            error = {pointInput.error_y}
          />
          <PointInput
            coord= 'r [-5,3]'
            value={pointInput.r}
            onChange={(e) => handleOnChange('r', e)}
            error = {pointInput.error_r}
          />
          <Button icon='login' label='Submit' onClick={handleOnSubmit} raised primary 
            disabled={!isValid} />
        </CardText>
      </Card>
      <ErrorDialog
        
      />
    </section>
  )
}

export default PointForm