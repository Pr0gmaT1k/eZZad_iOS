//
//  ViewController.swift
//  eZZad_iOS
//
//  Created by AzerTy on 06/03/2017.
//  Copyright © 2017 Pr0gmaT1k. All rights reserved.
//

import UIKit
import MapKit

class ViewController: UIViewController, MKMapViewDelegate {
  // Mark: IBoutlet
  @IBOutlet private weak var mapView: MKMapView!
  
  // Mark: public func
  override func viewDidLoad() {
    super.viewDidLoad()
    self.mapView.delegate = self
    
    //Center map
    let center = CLLocationCoordinate2D(latitude: 47.346471, longitude: -1.720943)
    let viewRegion : MKCoordinateRegion = MKCoordinateRegionMakeWithDistance(center, 2000, 2000);
    let adjustedRegion : MKCoordinateRegion = self.mapView.regionThatFits(viewRegion)
    self.mapView.setRegion(adjustedRegion ,animated:true)
    self.mapView.showsUserLocation = true
    
    // Initialise DB
    if let dbPath = Bundle.main.url(forResource: "zad", withExtension: "mbtiles")?.path {
      let overlay = MBtilesOverlay(dbPath: dbPath)
      overlay.canReplaceMapContent = true
      mapView.add(overlay, level: .aboveLabels)
    }
  }
  
  
  func mapView(_ mapView: MKMapView, rendererFor overlay: MKOverlay) -> MKOverlayRenderer {
    guard let tileOverlay = overlay as? MKTileOverlay else { return MKOverlayRenderer() }
    return MKTileOverlayRenderer(tileOverlay: tileOverlay)
  }
}

