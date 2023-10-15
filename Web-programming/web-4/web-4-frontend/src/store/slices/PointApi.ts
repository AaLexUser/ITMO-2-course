import {createApi, fetchBaseQuery } from '@reduxjs/toolkit/query/react'
import Point from '../../types/Point'
import PointResponse from '../../types/PointResponse'
import { serverHost } from '../../utils/config'


export const pointApi = createApi({
  reducerPath: 'pointApi',
  tagTypes: ['Points'],
  baseQuery: fetchBaseQuery({
    baseUrl: serverHost + 'api/v1/', 
    headers: {
      'Access-Control-Allow-Origin': serverHost + 'api/*',
    }
  }),
  endpoints: (build) => ({
    getPoints: build.query<PointResponse[], string>({
      query:(token) => ({
        url: 'get-points',
        headers: {
          'Authorization': 'Bearer ' + token
        }
      }),
      providesTags: (result) =>
        result
          ? [
            ...result.map(({ id }) => ({ type: 'Points' as const, id })),
            { type: 'Points', id: 'LIST' },
          ]
          : [{ type: 'Points', id: 'LIST' }],
    }),
    addPoint: build.mutation<void, {token: string, body: Point}>({
      query: ({token, body}) => ({
        url: 'add-point',
        method: 'POST',
        body,
        headers: {
          'Authorization': 'Bearer ' + token
        }
      }),
      invalidatesTags: [{type: 'Points', id: 'LIST'}]
    }),
    deletePoint: build.mutation<void, {token: string, id: number | string}> ({
      query: ({token, id }) => ({
        url: 'delete/'+ id,
        method: 'DELETE',
        headers:{
          'Authorization': 'Bearer ' + token
        }
      }),
      invalidatesTags: [{type: 'Points', id: 'LIST'}]
    }),
    updatePoint: build.mutation<void, {token: string, id: number | string, body: Point}> ({
      query: ({token, id, body }) => ({
        url: 'update/'+ id,
        method: 'PUT',
        body,
        headers:{
          'Authorization': 'Bearer ' + token
        }
      }),
      invalidatesTags: [{type: 'Points', id: 'LIST'}]
    }),
  })
})

export const {useGetPointsQuery, useAddPointMutation, useDeletePointMutation, useUpdatePointMutation} = pointApi

