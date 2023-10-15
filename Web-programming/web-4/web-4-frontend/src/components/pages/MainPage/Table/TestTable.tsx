
import React from 'react'
import { useAppSelector } from '../../../../utils/hook'
import { useGetPointsQuery } from '../../../../store/slices/PointApi'


const TableBody = ({rows}) =>{
  return (
    <tbody>
      {
        rows.map(item => {
          return (
            <tr>
              <td>{item.x}</td>
              <td>{item.y}</td>
              <td>{item.r}</td>
              <td>{item.hitResult}</td>
              <td>{item.time}</td>
              <td>{item.executionTime}</td>
            </tr>
          )
        })
      }
    </tbody>
  )
}
const TableTest = () => {
  const token = useAppSelector(state => state.user).user.token
  const {data = [] } = useGetPointsQuery(token)

  return (
    <table>
      <thead>
        <tr>
          <th>X</th>
          <th>Y</th>
          <th>R</th>
          <th>hitResult</th>
          <th>time</th>
          <th>executionTime</th>
        </tr>
      </thead>
      <TableBody
        rows= {data}/>
    </table>
  )
}
export default TableTest