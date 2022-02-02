import './index.scss'

const getDims = (elm, removeBorder = true, removePadding = true) => {
  const elmStyles = window.getComputedStyle(elm)
  return {
    height: elm.offsetHeight +
      (removeBorder ? -parseInt(elmStyles.borderTopWidth, 10) - parseInt(elmStyles.borderBottomWidth, 10) : 0) +
      (removePadding ? -parseInt(elmStyles.paddingTop, 10) - parseInt(elmStyles.paddingBottom, 10) : 0),
    width: elm.offsetWidth +
      (removeBorder ? -parseInt(elmStyles.borderLeftWidth, 10) - parseInt(elmStyles.borderRightWidth, 10) : 0) +
      (removePadding ? -parseInt(elmStyles.paddingLeft, 10) - parseInt(elmStyles.paddingRight, 10) : 0)
  }
}

const clockwiseRotate = (center, angle, point) => {
  const movex = point.x - center.x
  const movey = point.y - center.y

  const s = Math.sin(angle * Math.PI / 180)
  const c = Math.cos(angle * Math.PI / 180)

  const x = movex * c - movey * s
  const y = movex * s + movey * c

  return {
    x: x + center.x,
    y: y + center.y
  }
}

const clock = document.getElementsByClassName('clock')[0]
const {height: boxH, width: boxW} = getDims(clock, false, false)
const minv = Math.min(boxH, boxW)
clock.style.height = clock.style.width = minv

const {height, width} = getDims(clock)
let dialHours = document.getElementsByClassName('clock__dial-hour')
let offsetFix = dialHours[11].offsetHeight / 10
let refx = 0
let refy = -height / 2 + dialHours[11].offsetHeight / 2
const origin = {x: 0, y: 0}

for (let i = 1; i <= 12; ++i) {
  let newc = clockwiseRotate(origin, 30, {x: refx, y: refy})
  refx = Math.round(newc.x)
  refy = Math.round(newc.y)
  newc.x = Math.round(newc.x - dialHours[i - 1].offsetWidth / 2 + width / 2)
  newc.y = Math.round(newc.y - dialHours[i - 1].offsetHeight / 2 + height / 2 + offsetFix)
  dialHours[i - 1].style.top = newc.y + 'px'
  dialHours[i - 1].style.left = newc.x + 'px'
}

const handPivot = document.getElementById('hand-pivot')
const pivotBoxDims = getDims(handPivot, false, false)
handPivot.style.top = height / 2 - pivotBoxDims.height / 2 + 'px'
handPivot.style.left = width / 2 - pivotBoxDims.width / 2 + 'px'

const hoursHand = document.getElementById('hours-hand')
const minutesHand = document.getElementById('minutes-hand')
const secondsHand = document.getElementById('seconds-hand')
const offByPivot = 0.05 * height

const hoursHandDims = getDims(hoursHand, false, false)
hoursHand.style.top = 1.6 * dialHours[11].offsetHeight + 'px'
hoursHand.style.left = width / 2 - hoursHandDims.width / 2 + 'px'
hoursHand.style.height = (height / 2 - 1.6 * dialHours[11].offsetHeight + offByPivot) + 'px'
hoursHand.style.transformOrigin = `${hoursHandDims.width / 2}px ${hoursHand.offsetHeight - offByPivot}px`

const minutesHandDims = getDims(minutesHand, false, false)
minutesHand.style.top = 1.2 * dialHours[11].offsetHeight + 'px'
minutesHand.style.left = width / 2 - minutesHandDims.width / 2 + 'px'
minutesHand.style.height = (height / 2 - 1.2 * dialHours[11].offsetHeight + offByPivot) + 'px'
minutesHand.style.transformOrigin = `${minutesHandDims.width / 2}px ${minutesHand.offsetHeight - offByPivot}px`

const secondsHandDims = getDims(minutesHand, false, false)
secondsHand.style.top = dialHours[11].offsetHeight + 'px'
secondsHand.style.left = width / 2 - secondsHandDims.width / 2 + 'px'
secondsHand.style.height = (height / 2 - dialHours[11].offsetHeight + offByPivot) + 'px'
secondsHand.style.transformOrigin = `${secondsHandDims.width / 2}px ${secondsHand.offsetHeight - offByPivot}px`

const dt = new Date()
const secsElpased = dt.getSeconds()
const minsElapsed = dt.getMinutes() + secsElpased / 60
const hrsElapsed = dt.getHours() % 12 + minsElapsed / 60

const rotate = (elm, deg) => {
  elm.style.transform = `rotate(${deg}deg)`
}
const init = () => {
  let hrsRotn = hrsElapsed * 360 / 12
  let minsRotn = minsElapsed * 360 / 60
  let secsRotn = secsElpased * 360 / 60
  rotate(hoursHand, hrsRotn)
  rotate(minutesHand, minsRotn)
  rotate(secondsHand, secsRotn)
  setTimeout(() => (secondsHand.style.transition = 'transform 1s linear'), 0)
  setInterval(() => {
    // do %360
    hrsRotn += 360 / (3600 * 12)
    minsRotn += 360 / (60 * 60)
    secsRotn += 360 / 60
    rotate(hoursHand, hrsRotn)
    rotate(minutesHand, minsRotn)
    rotate(secondsHand, secsRotn)
  }, 1000)
}
init()
