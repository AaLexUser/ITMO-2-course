import React from 'react'
import WelcomePage from './pages/WelcomePage'
import SignUpPage from './pages/AuthPage/SignUpPage'
import MainLayout from './Layout'
import NotFoundPage from './pages/NotFoundPage'
import {Route, Routes} from 'react-router-dom'
import MainPage from './pages/MainPage/MainPage'
import SignInPage from './pages/AuthPage/SignInPage'
import ProfilePage from './pages/Profile/ProfilePage'
import ProfileSettings from './pages/Profile/ProfileSettings'
export const App = () => {
  return (
    <div>
      <Routes>
        <Route path='/' element={<MainLayout/>}>
          <Route index element={<WelcomePage/>}/>
          <Route path="sign-up" element={<SignUpPage/>}/>
          <Route path="sign-in" element={<SignInPage/>}/>
          <Route path="profile" element={<ProfilePage/>}/>
          <Route path="settings" element={<ProfileSettings/>}/>
          <Route path='main' element={<MainPage/>}/>
          <Route path="*" element={<NotFoundPage/>}/>
        </Route>
      </Routes>
    </div>
  )
}
