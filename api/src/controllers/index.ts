import * as express from 'express';

export default function hello(
  req: express.Request,
  res: express.Response,
  next: express.NextFunction,
) {
  return res.json({ response: 'Hello, world' });
}
