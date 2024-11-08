module.exports = {
    NODE_ENV: process.env.NODE_ENV || 'development',
    HOST: process.env.HOST || '127.0.0.1',
    PORT: process.env.PORT || 3000,
    DB_URL: process.env.DB_URL || 'mongodb://localhost:27017/my-db',
    MONGO_DB_USERNAME: process.env.MONGO_DB_USERNAME || 'root',
    MONGO_DB_PWD: process.env.MONGO_DB_PWD || 'example',
    }