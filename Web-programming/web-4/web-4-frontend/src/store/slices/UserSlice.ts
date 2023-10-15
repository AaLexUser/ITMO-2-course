import {createSlice, PayloadAction} from '@reduxjs/toolkit'

type User = {
  username: string,
  password: string,
  token: string
}

type UserState = {
  user: User
}

const initialState: UserState = {
  user:{
    username: '',
    password: '',
    token: ''
  }
}

export const userSlice = createSlice({
  name: 'user',
  initialState,
  reducers: {
    setUser: (state, action: PayloadAction<User>) => {
      state.user = action.payload
    },
    resetUser: (state) => {
      return state = initialState
    }
  }
})

export const selectUser = state => state.user

export const {setUser, resetUser} = userSlice.actions

export default userSlice.reducer