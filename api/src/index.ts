import * as express from 'express';

import hello from './controllers/';

/**
 * Create Express server.
 */
const app = express();

/**
 * Express configuration(s).
 */
app.set('port', process.env.PORT || 3005);

/**
 * CORS.
 */
app.use(
  (req: express.Request, res: express.Response, next: express.NextFunction) => {
    res.header('Access-Control-Allow-Origin', '*');
    res.header(
      'Access-Control-Allow-Headers',
      'Origin, X-Requested-With, Content-Type, Accept',
    );
    next();
  },
);

/**
 * Primary app route(s).
 */
app.get('/hello', hello);

/**
 * Start Express server.
 */
app.listen(app.get('port'), () => {
  console.log(
    'App now running at http://localhost:%d in %s mode.',
    app.get('port'),
    app.get('env'),
  );
  console.log('Press Ctrl+C to stop.');
});
