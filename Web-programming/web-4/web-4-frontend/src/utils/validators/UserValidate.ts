import { validateHeaderName } from 'http'

export const validate = (name: string, value: string | undefined):boolean => {
  if(name === 'username'){
    return usernameValidate(value)
  }
  if(name === 'password'){
    return passwordValidate(value)
  }
  return false
}

export const usernameValidate = (username: string | undefined): boolean => {
  if(username === undefined || username === ''){
    return false
  }
  const rExp: RegExp =  /^[A-Za-z0-9]{8,}$/g
  const res = username.match(rExp)
  if (res != null ){
    if(res[0] === username){
      return true
    }
    return false
  }
  return false

}
export const usernameValidateString = (username: string | undefined): string => {
  if(usernameValidate(username) && username ){
    return username
  }
  else return ''
}

export const passwordValidate = (password: string | undefined):boolean => {
  if(password === undefined || password === ''){
    return false
  }
  const rExp: RegExp =  /^(?=.*[0-9])(?=.*[a-zA-z])(?=\S+$).{8,}$/g
  const res = password.match(rExp)
  if (res != null ){
    if(res[0] === password){
      return true
    }
    return false
  }
  return false
}
export const passwordValidateString = (password: string | undefined): string => {
  if(passwordValidate(password) && password){
    return password
  }
  else return ''
}