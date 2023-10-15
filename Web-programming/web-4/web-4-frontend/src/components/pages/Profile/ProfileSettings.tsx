import React, {useEffect, useState} from 'react'
import { useAppDispatch, useAppSelector } from '../../../utils/hook'
import { resetUser } from '../../../store/slices/UserSlice'
import { Card, CardTitle, CardText } from 'react-toolbox/lib/card'
import Button from 'react-toolbox/lib/button'
import ProgressBar from 'react-toolbox/lib/progress_bar'
import { useNavigate } from 'react-router-dom'
import Input from 'react-toolbox/lib/input'
import { useGetAvatarQuery, useSetAvatarMutation, useDeleteUserMutation } from '../../../store/slices/UserApi'
import _Avatar from '../../../types/Avatar'

const ProfileSettings = () => {
  const user = useAppSelector(state => state.user).user
  const token = useAppSelector(state => state.user).user.token
  const {data= {url: ''}, isLoading } = useGetAvatarQuery(token)
  const [setAvatar, {isSuccess}] = useSetAvatarMutation()
  const [deleteUser, {isSuccess: isDeleteSuccess}] = useDeleteUserMutation()

  const [urlInput, setUrlInput] = useState('')
  const nav = useNavigate()
  const dispatch = useAppDispatch()
  useEffect(()=> {if (!isLoading && data) setUrlInput(data.url) }, [data])
  const handleOnSave = async () => {
    await setAvatar({token: token, body: {url: urlInput}}).unwrap()
  }
  const handleOnDelete = async () => {
    await deleteUser(token).unwrap()
  }
  useEffect(()=> {
    if(isDeleteSuccess){ 
      nav('/', { replace: true })
      dispatch(resetUser())
    }
  }, [isDeleteSuccess])
  useEffect(()=> {if (isSuccess) nav('/main') }, [isSuccess])
  if (isLoading) return (
    <section>
      <h1>Loading...</h1>
      <ProgressBar type="circular" mode="indeterminate" />
    </section>)
  return (
    <section style={{display: 'flex', alignItems: 'center', justifyContent: 'center', height:'600px'}}>
      <Card style={{width: '30rem'}}>
        <CardTitle title='Profile Settings'/>
        <CardText>
          <Input type='text' 
            label='Avatar URL'
            icon='image'
            name='username'
            value={urlInput}
            required
            onChange={(e) => setUrlInput(e)}
          />
        </CardText>
        <Button label='Save' onClick={handleOnSave} raised primary />
        <Button label='Delete Account' onClick={handleOnDelete} raised accent />
      </Card>
    </section>
  )
}
export default ProfileSettings 