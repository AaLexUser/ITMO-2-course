import React, {useEffect, useState} from 'react'
import { useNavigate } from 'react-router-dom'
import AppBar from 'react-toolbox/lib/app_bar'
import Navigation from 'react-toolbox/lib/navigation'
import Avatar from 'react-toolbox/lib/avatar'
import { useSelector } from 'react-redux'
import { selectUser } from '../../store/slices/UserSlice'
import Button from 'react-toolbox/lib/button'
import { useGetAvatarQuery } from '../../store/slices/UserApi'

const Navbar = () => {
  const user = useSelector(selectUser)
  const nav = useNavigate()
  const {data= {url: ''}, isLoading } = useGetAvatarQuery(user.user.token)
  const authStatus = user.user.username !== '' ? true : false
  return (
    <AppBar
      title="WEB LAB 4"
      leftIcon="radio_button_unchecked"
      onLeftIconClick={() => nav('/', { replace: true })}
    >
      <p style={{fontFamily: 'Dancing Script, cursive'}}> Alexey Lapin P32101 variant #3210173</p>
      <Navigation type="horizontal">
        <Button 
          label= 'Main Page'
          onClick={() => nav( `${authStatus ? '/main' : '/sign-in'}`, { replace: false })}
          style = {{
            color: 'white'
          }}
          flat
        />
        <Button 
          label= {user.user.username !== '' ? user.user.username : 'Sign In'} 
          onClick={() => nav( `${authStatus ? '/profile' : '/sign-in'}`, { replace: false })}
          style = {{
            color: 'white'
          }}
          flat
        />

      </Navigation>
      {authStatus &&
        <Avatar onClick={() => nav('/profile', { replace: false })} title={user.user.username.toUpperCase()}
          style={{backgroundColor: 'deepskyblue'}}>
          {data.url && data.url !=='' && <img src={data.url}/>}
        </Avatar>}
    </AppBar>
  )
}

export default Navbar
