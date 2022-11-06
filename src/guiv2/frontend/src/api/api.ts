import { Point } from "../types/types";

class Api {
  private socket: WebSocket;  
  private connected = false;

  private readonly possibleReponses = ["updated-path"];

  public readonly callbacks: {
    [key in typeof this.possibleReponses[number]]: ((tokens: string[]) => void)[];
  } = this.possibleReponses.reduce((obj: typeof this.callbacks, key) => {
    obj[key] = [];
    return obj;
  }, {});

  public readonly onopen: ((e: Event) => void)[] = [];

  constructor() {
    this.socket = new WebSocket("ws://localhost:9002");

    this.socket.onopen = (e) => {
      console.log("Connected to socket successfully!");
      this.connected = true;

      for (const callback of this.onopen)
        callback(e);
    };

    this.socket.onmessage = (msg: MessageEvent<any>) => {
      const tokens = (msg.data as string).split(/\s+/);

      if (tokens[0] === "ERROR") {
        throw new Error(`Something went wrong. Message: "${tokens[1]}"`);
      } else {
        this.handleResponse(tokens);
      }
    };

    this.socket.onerror = (e) => {
      console.error("An unexpected error occured.", e);
    };
  }

  public isConnected = () => {
    return this.connected;
  }

  private handleResponse = (tokens: string[]) => {
    if (tokens[0] in this.callbacks) {
      for (const callback of this.callbacks[tokens[0]]) {
        callback(tokens);
      }
    } else {
      throw new Error(`Unrecognized message recieved. Tokens: ${tokens}`)
    }
  };

  public pathUpdated = (points: Point[]) => {
    this.socket.send("update-path");
  };
}

export default Api;
