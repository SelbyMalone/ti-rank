//Creates paths for scripts
const path = require('path')

module.exports = function override(config) {
  config.resolve.alias = {
    ...config.resolve.alias,
    js: path.resolve(__dirname, 'src/js')
    public: path.resolve(__dirname, 'public')
  };
  return config;
}
