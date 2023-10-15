import React from 'react'
import { useAppDispatch, useAppSelector } from '../../../utils/hook'
import { resetUser } from '../../../store/slices/UserSlice'
import { Card, CardTitle, CardText, CardMedia} from 'react-toolbox/lib/card'
import Button from 'react-toolbox/lib/button'
import { useNavigate } from 'react-router-dom'
import Navigation from 'react-toolbox/lib/navigation'
import { useGetAvatarQuery } from '../../../store/slices/UserApi'
import ProgressBar from 'react-toolbox/lib/progress_bar'

const ProfilePage = () => {
  const user = useAppSelector(state => state.user).user
  const {data= {url: ''}, isLoading } = useGetAvatarQuery(user.token)
  const nav = useNavigate()
  const dispatch = useAppDispatch()
  const handleOnLogout = () =>{
    dispatch(resetUser())
    nav('/', { replace: true })
  }
  return (
    <section style={{display: 'flex', alignItems: 'center', justifyContent: 'center', height:'600px'}}>
      <Card style={{width: '350px'}}>
        <CardTitle title='Profile'/>
        {!isLoading
          ? <CardMedia aspectRatio="wide" image={data.url}/>
          :  <ProgressBar type="circular" mode="indeterminate" />}
        <CardText>
          <h3>Username: {user.username}</h3>
        </CardText>
        <Navigation type='horizontal'>
          <Button label='Logout' onClick={handleOnLogout} raised accent />
          <Button label='Settings' onClick={()=> nav('/settings', { replace: false })} raised flat />
        </Navigation>
      </Card>
    </section>
  )
}
export default ProfilePage