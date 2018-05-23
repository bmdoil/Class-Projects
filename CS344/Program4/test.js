const request = require('request');
request({
  method: 'POST',
  url: 'https://api.idex.market/returnTicker',
  json: {
    market: 'ETH_SAN'
  }
}, function (err, resp, body) {
  console.log(body);
})