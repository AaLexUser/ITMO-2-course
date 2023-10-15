import {createSlice, PayloadAction} from '@reduxjs/toolkit'
export type PointInputState = {
  x: string
  y: string
  r: string
  error_x: string
  error_y: string
  error_r: string
}
const initialState: PointInputState = {
  x: '',
  y: '',
  r: '',
  error_x: '',
  error_y: '',
  error_r: '',
}
export const pointInputSlice = createSlice({
  name: 'pointInput',
  initialState,
  reducers:{
    setInput: (state, action: PayloadAction<PointInputState>) => {
      return state = action.payload
    },
    resetInput: (state) => {
      return state = initialState
    }
  }

})
export const {setInput, resetInput} = pointInputSlice.actions
export default pointInputSlice.reducer