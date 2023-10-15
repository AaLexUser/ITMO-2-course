import {createSlice, PayloadAction, PrepareAction} from '@reduxjs/toolkit'
import { usernameValidateString, passwordValidateString, validate } from '../../utils/validators/UserValidate'
export type AuthState = {
  username: string
  password: string
  error_username: string,
  error_password: string,
}
const initialState: AuthState = {
  username: '',
  password: '',
  error_username: '',
  error_password: '',
}
export const authSlice = createSlice({
  name: 'auth',
  initialState,
  reducers:{
    setAuth: (state, action: PayloadAction<AuthState>) => {
      return state = action.payload
    },
    resetAuth: (state) => {
      return state = initialState
    }
  }

})
export const {setAuth, resetAuth} = authSlice.actions
export default authSlice.reducer