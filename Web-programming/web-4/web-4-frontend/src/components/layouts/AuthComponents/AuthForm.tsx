import React from 'react'
import Input from 'react-toolbox/lib/input'
import { AuthState } from '../../../store/slices/AuthSlice'
import { useAppSelector} from '../../../utils/hook'
interface AuthFormProps{
  handleChange: (name: string, value: string) => void,
}

const AuthForm: React.FC<AuthFormProps> = ({ handleChange}) => {
  const _state: AuthState = useAppSelector(state => state.auth)

  return (
    <section>
      <Input type='text' 
        label='Name'
        icon='person'
        name='username'
        value={_state.username}
        required
        onChange={handleChange.bind(this, 'username')}
        maxLength={16 } error={_state.error_username}/>
      <Input type='password'
        label='Password'
        icon='password'
        name='password' 
        value={_state.password} 
        required
        onChange={handleChange.bind(this,'password')} 
        maxLength={32 } 
        error={_state.error_password}/>
    </section>
  )
}

export default AuthForm