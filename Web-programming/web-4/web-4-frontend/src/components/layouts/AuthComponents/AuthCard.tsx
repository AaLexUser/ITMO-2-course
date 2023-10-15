import React from 'react'
import { Card, CardTitle, CardText, CardActions } from 'react-toolbox/lib/card'
import AuthFrom from './AuthForm'
import Button from 'react-toolbox/lib/button'
import ErrorDialog from '../ErrorDialog'
import { validate } from '../../../utils/validators/UserValidate'
import { AuthState } from '../../../store/slices/AuthSlice'
import { useAppSelector, useAppDispatch } from '../../../utils/hook'
import { setAuth } from '../../../store/slices/AuthSlice'
import Navigation from 'react-toolbox/lib/navigation'
import {useNavigate} from 'react-router-dom'

interface AuthCardProps{
  title: string,
  handleOnSubmit: () => void,
  rightButtonTitle: string,
  onRightButtonClick: () => void
}

const AuthCard: React.FC<AuthCardProps> = ({title, handleOnSubmit,rightButtonTitle, onRightButtonClick}) => {
  const _state: AuthState = useAppSelector(state => state.auth)
  const dispatch = useAppDispatch()
  const nav = useNavigate()
  const handleChange = (name: string, value: string) => {
    const error_field = `error_${[name]}`
    if (validate(name, value)) {
      dispatch(setAuth
      (({
        ..._state,
        [name]: value,
        [error_field]: '',
      })
      )
      )
    } else {
      dispatch(setAuth({
        ..._state,
        [name]: value,
        [error_field]: 'Invalid ' + [name],
      }))
    }
  }
  return (
    <section style={{display: 'flex', alignItems: 'center', justifyContent: 'center', height:'600px'}}>
      <Card style={{width: '350px'}}>
        <CardTitle title={title}/>
        <CardText>
          <AuthFrom 
            handleChange={handleChange}
          />
          <Navigation type='horizontal'>
            <Button icon='login' label='Submit' onClick={handleOnSubmit} raised primary disabled={
              _state.error_password !== '' || _state.error_username !== '' || _state.username === '' || _state.password === ''} />
            <Button label={rightButtonTitle} flat onClick={onRightButtonClick}/>
          </Navigation>
          
        </CardText>
        
        <CardActions>
        </CardActions>
      </Card>
      <ErrorDialog/>
    </section>
  )
}

export default AuthCard