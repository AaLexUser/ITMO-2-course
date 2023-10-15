import React, {useEffect} from 'react'
import { useAppSelector } from '../../../utils/hook'
import {selectUser} from '../../../store/slices/UserSlice'
import PointForm from './PointForm/PointForm'
import { useNavigate } from 'react-router-dom'
import { Card, CardTitle, CardText, CardMedia } from 'react-toolbox/lib/card'
import PointsTable from './Table/PointsTable'
import TestTable from './Table/TestTable'
import CardGraph from './Graph/CardGraph'
import Navigation from 'react-toolbox/lib/navigation'

const MainPage = () => {
  const user = useAppSelector(state => state.user)
  const nav = useNavigate()
  const authStatus = user.user.username !== '' ? true : false
  useEffect(
    ()=> {if(!authStatus) nav('/sign-in')}
    , [authStatus])
  return (
    <Card className='wrapper' style={{
      width: '100%',
      height: '100%', 
    }}>
      <CardTitle title='MainPage'/>
      <CardText style={{
        display: 'flex',
        flexDirection: 'column',
        justifyContent: 'space-around'
      }}>
        <div style={{
          display: 'flex',
          flexWrap: 'wrap',
          
        }}>
          <PointForm/>
          <CardGraph/>
        </div>
        <PointsTable/>
      </CardText>
    </Card>
  
  )
}

export default MainPage