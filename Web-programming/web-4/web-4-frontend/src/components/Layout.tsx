import React from 'react'
import Navbar from './layouts/Navbar'
import { Outlet } from 'react-router-dom'

const MainLayout = () => {
  return (
    <div>
      <header>
        <Navbar />
      </header>

      <Outlet />

      <footer></footer>
    </div>
  )
}

export default MainLayout
