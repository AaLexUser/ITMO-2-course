import React, {useEffect} from 'react'
import { useAppSelector } from '../../../../utils/hook'
import { Card, CardTitle, CardText, CardMedia } from 'react-toolbox/lib/card'
import { useNavigate } from 'react-router-dom'
import CanvasGraph from './CanvasGraph'

const CardGraph = () => {
  const user = useAppSelector((state) => state).user
  const nav = useNavigate()
  return (
    <Card style={{
      width: 'auto', 
      height: 'auto',
      margin: '0.1rem'}}>
      <CardTitle title='Graph'/>
      <CardText>
        <CanvasGraph/>
      </CardText>
    </Card>
  
  )
}

export default CardGraph