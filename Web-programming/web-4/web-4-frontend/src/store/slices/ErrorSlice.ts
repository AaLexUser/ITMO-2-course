import {createSlice, PayloadAction} from '@reduxjs/toolkit'
export type Error = {
  active: boolean,
  msg: string
}
const initialState: Error = {
  active: false,
  msg: ''
}
export const errorSlice = createSlice({
  name: 'error',
  initialState,
  reducers:{
    setError: (state, action: PayloadAction<Error>) => {
      return state = action.payload
    },
    resetError: (state) => {
      return state = initialState
    }
  }

})
export const {setError, resetError} = errorSlice.actions
export default errorSlice.reducer
