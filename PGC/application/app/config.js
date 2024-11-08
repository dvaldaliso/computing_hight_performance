module.exports = {
    NODE_ENV: process.env.NODE_ENV || 'development',
    HOST: process.env.HOST || '127.0.0.1',
    PORT: process.env.PORT || 3000,
    MONGO_URL: process.env.MONGO_URL || 'mongodb://localhost:27017',
    MONGO_DB_USERNAME: process.env.MONGO_USER || 'root',
    MONGO_DB_PWD: process.env.MONGO_PASSWORD || 'example',
    }