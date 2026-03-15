function first_functions(){
    // await new Promise(resolve => setTimeout(resolve, 3000));
    //sleep for 3 seconds
    setTimeout(() => {        console.log("first functions")
    }, 3000);
    return 1222222;
}

async function async_functions(){
    // sleep for 3 seconds
    value = await first_functions()
    return value
}


console.log("before then functions")
// console.log(async_functions())
v =  async_functions().then(v => console.log(v))
console.log("immediatlly after then functions ")

console.log(v)
