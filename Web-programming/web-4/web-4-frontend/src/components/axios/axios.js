import axios from 'axios'
import { serverHost } from '../../utils/config'
export const instance = axios.create({
  baseURL: serverHost + 'api/v1/',
  headers: {
    'Access-Control-Allow-Origin': '*'
  }
})
export default instance