import React, {useEffect, useState} from 'react'
import Table from 'react-toolbox/lib/table'
import UpdateRowDialog from './UpdateRowDialog'
import dateFormat from 'dateformat'
import { useGetPointsQuery, useDeletePointMutation } from '../../../../store/slices/PointApi'
import { useAppSelector } from '../../../../utils/hook'
import {instance as _axios} from '../../../axios/axios'
import ProgressBar from 'react-toolbox/lib/progress_bar'
import Point from '../../../../types/Point'
import { DataGrid, GridColDef, GridValueGetterParams } from '@mui/x-data-grid'
import PointString from '../../../../types/PointString'
import Button from 'react-toolbox/lib/button'
import Pagination from '@mui/material/Pagination'
import { GridRowId , GridCellParams} from '@mui/x-data-grid'
import {
  GridToolbarContainer,
  GridToolbarColumnsButton,
  GridToolbarFilterButton,
  GridToolbarExport,
  GridToolbarDensitySelector,
  gridPageCountSelector,
  gridPageSelector,
  useGridApiContext,
  useGridSelector,
} from '@mui/x-data-grid'
import PointResponse from '../../../../types/PointResponse'



const columns: GridColDef[] = [
  {field: 'x', headerName: 'X'},
  {field: 'y', headerName: 'Y'},
  {field: 'r', headerName: 'R'},
  {field: 'hitResult', headerName: 'isHit?'},
  {field: 'time', headerName: 'Time', width: 180},
  {field: 'executionTime', headerName: 'ex. Time ms'},
  {field: 'username', headerName: 'User'},
]
const DeleteButton = ({onDeleteHandle}) => {
  const apiRef = useGridApiContext()
  const page = useGridSelector(apiRef, gridPageSelector)
  const pageCount = useGridSelector(apiRef, gridPageCountSelector)
  return (
    <GridToolbarContainer>
      <Button label='Delete' onClick={onDeleteHandle} raised accent />
      <GridToolbarColumnsButton />
      <GridToolbarFilterButton />
      <GridToolbarDensitySelector />
      <GridToolbarExport />
      <Pagination
        color="primary"
        count={pageCount}
        page={page + 1}
        onChange={(event, value) => apiRef.current.setPage(value - 1)}
      />
    </GridToolbarContainer>
  )
}

const PointsTable = () => {
  const token = useAppSelector(state => state.user).user.token
  const {data = [], isLoading, isSuccess } = useGetPointsQuery(token)
  const [table, setTable ] = useState<PointString[]>([])
  const [deleteRow, {}] = useDeletePointMutation()
  const [selected, setSelected] = useState<GridRowId[]>([])
  const [updateDialog, setUpdateDialog] = useState<{active: boolean, event?: PointString}>({active: false})
  const onDeleteHandle = () => {
    selected.map(async (id)=>{
      await deleteRow({token: token, id: id})
    })
  }
  useEffect(()=> {
    if (isSuccess) setTable([...data].map((point: PointResponse) => {
      return {
        ...point,
        hitResult: point.hitResult ? 'hit': 'miss',
        time: dateFormat(point.time, 'd mmm yyyy H:MM:ss')
      }
    }))
  }, [data])
  return (
    <div style={{ height: '30rem', width: '100%', margin: '0.1rem' }}>
      {isLoading && <ProgressBar type="linear" mode="indeterminate" />}
      <DataGrid
        components={{
          Footer: DeleteButton,
        }}
        componentsProps={{
          footer: {onDeleteHandle : onDeleteHandle },
        }}
        rows={table}
        columns={columns}
        pageSize={10}
        rowsPerPageOptions={[5, 10]}
        checkboxSelection
        onSelectionModelChange={(e) => setSelected(e)}
        onCellDoubleClick={(e)=> setUpdateDialog({active: true, event: e.row})}
      />
      <UpdateRowDialog 
        updateState = {updateDialog}
        setUpdateState = {setUpdateDialog}
      />
    </div>
  )
}

export default PointsTable