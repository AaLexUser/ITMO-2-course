import {createApi, fetchBaseQuery } from '@reduxjs/toolkit/query/react'
import _Avatar from '../../types/Avatar'
import { serverHost } from '../../utils/config'

export const userApi = createApi({
  reducerPath: 'userApi',
  tagTypes: ['User'],
  baseQuery: fetchBaseQuery({
    baseUrl: serverHost + 'api/v1/', 
    headers: {
      'Access-Control-Allow-Origin': serverHost + 'api/*',
    }
  }),
  endpoints: (build) => ({
    getAvatar: build.query<_Avatar, string>({
      query:(token) => ({
        url: 'get-avatar',
        headers: {
          'Authorization': 'Bearer ' + token
        }
      }),
      providesTags: [{ type: 'User', id: 'USER' }]
    }),
    setAvatar: build.mutation<void, {token: string, body: {url: string}}>({
      query: ({token, body}) => ({
        url: 'set-avatar',
        method: 'POST',
        body,
        headers: {
          'Authorization': 'Bearer ' + token
        }
      }),
      invalidatesTags: [{type: 'User', id: 'USER'}]
    }),
    deleteUser: build.mutation<void, string> ({
      query:(token) => ({
        url: 'delete-user',
        method: 'DELETE',
        headers: {
          'Authorization': 'Bearer ' + token
        }
      }),
      invalidatesTags: [{type: 'User', id: 'USER'}]
    })
  })
})

export const {useGetAvatarQuery, useSetAvatarMutation, useDeleteUserMutation} = userApi

