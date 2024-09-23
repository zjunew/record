import time
import asyncio
import pyppeteer as pyp
async  def antiAntiCrawler(page):
    await page.setUserAgent('Mozilla/5.0(Windows NT 6.1;\
        Win64;x64) AppleWebKit/537.36 (KHTML, like Gecko)\
            Chrome/78.0.3904.70 Safari/537.36          ')
    await page.evaluateOnNewDocument(
        '() =>{ Object.defineProperties(navigator,\
        webdriver:{ get: () => false}})}')
async def Seize_classes(loginUrl):
    width,height=1400,800
    browser=await pyp.launch(headless=False,userdataDir="C:\vscode\All kinds of\
                              projects\python\python_spider",\
                             args=[f'--window-size={width},{height}'])
    page=await browser.newPage()
    await antiAntiCrawler(page)
    await page.setViewport({'width':width,'height':height})
    await page.goto(loginUrl)
    element=await page.querySelector("#ssodl")
    await element.click()
    await page.waitForSelector("#dl",
                               timeout=10000)
    
    element=await page.querySelector("#username")
    await element.type("")#/////////输入学号
    element=await page.querySelector("#password")
    await element.type("")#/////////输入密码
    element=await page.querySelector("#dl")
    await element.click()
    
    
    await page.waitForSelector("body > div:nth-child(4) > div > nav > ul > li:nth-child(2)",
                               timeout=40000)
    
    element=await page.querySelector('body > div:nth-child(4) > div > nav > ul > li:nth-child(2)')
    await element.click()
    
    element=await page.querySelector("body > div:nth-child(4) > div > nav > ul > li.dropdown.open > ul > li:nth-child(4) > a")
    await element.click()
    await page.waitForNavigation()
    
    
    
    
def main():
    url='http://zdbk.zju.edu.cn/jwglxt/xtgl/login_slogin.html'
    asyncio.get_event_loop().run_until_complete(Seize_classes(url))
main()