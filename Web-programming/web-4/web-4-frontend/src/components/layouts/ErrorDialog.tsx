import React from 'react'
import Dialog from 'react-toolbox/lib/dialog'
import { useAppSelector, useAppDispatch } from '../../utils/hook'
import { Error } from '../../store/slices/ErrorSlice'
import { resetError } from '../../store/slices/ErrorSlice'

const ErrorDialog = () => {
  const actions = [
    { label: 'Close', onClick: () => dispatch(resetError())},
  ]

  const error: Error  = useAppSelector(state => state.error)
  const dispatch = useAppDispatch()
  return (
    <section>
      <Dialog
        actions={actions}
        active={error.active}
        onEscKeyDown={() => dispatch(resetError())}
        onOverlayClick={() => dispatch(resetError())}
        title={error.msg}
      >
      </Dialog>
    </section>
  )
}

export default ErrorDialog