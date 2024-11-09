module.exports = {
    NODE_ENV: process.env.NODE_ENV || 'development',
    HOST: process.env.HOST || '127.0.0.1',
    PORT: process.env.PORT || 3000,
    DB_URL: process.env.DB_URL || 'localhost:27017',
    MONGO_DB_USERNAME: process.env.MONGO_DB_USERNAME || 'admin',
    MONGO_DB_PWD: process.env.MONGO_DB_PWD || 'password',
    }