import {createSlice, PayloadAction} from '@reduxjs/toolkit'
import { PointInputState } from '../PointForm/PointInputSlice'
const initialState: PointInputState = {
  x: '',
  y: '',
  r: '',
  error_x: '',
  error_y: '',
  error_r: '',
}
export const updatePointInputSlice = createSlice({
  name: 'updatePointInput',
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
export const {setInput, resetInput} = updatePointInputSlice.actions
export default updatePointInputSlice.reducer