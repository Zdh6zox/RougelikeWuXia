// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class MapConstructorRegionDivision
{
};

class FVoronoiDiagramGeneratedSite
{
public:
    FVoronoiDiagramGeneratedSite(int32 InIndex, FVector2D InCoordinate, FVector2D InCentroid, FColor InColor, bool InIsCorner, bool InIsEdge);

    int32 Index;
    FColor Color;
    FVector2D Coordinate;
    FVector2D Centroid;
    TArray<class FVoronoiDiagramGeneratedEdge> Edges;
    TArray<FVector2D> Vertices;
    TArray<int32> NeighborSites;

    bool bIsCorner;
    bool bIsEdge;
};

class FVoronoiDiagramGeneratedEdge
{
public:
    FVoronoiDiagramGeneratedEdge(int32 InIndex, FVector2D InLeftEndPoint, FVector2D InRightEndPoint);

    int32 Index;
    FVector2D LeftEndPoint;
    FVector2D RightEndPoint;
};

class FVoronoiDiagram
{
public:
    /*
     *  Constructor
     *
     *  @param  InBounds    Rectangle that represents a 2D region for placing points
     */
    FVoronoiDiagram(FIntRect InBounds);

    /*
     *  Adds points to the diagram to be used at generation time
     *
     *  @param  Points  Array of integer points to be added.
     *  @return         True if added successful, false otherwise.  If false, no points are added.
     */
    bool AddPoints(const TArray<FIntPoint>& Points);

    /*
     *  Runs Fortune's Algorithm to generate sites with edges for the diagram
     */
    void GenerateSites(int32 RelaxationCycles);

    /*
     *  Bounds of the Voronoi Diagram
     */
    FIntRect Bounds;

    /*
     * Generated sites.  Filled after GenerateSites() is called
     */
    TMap<int32, FVoronoiDiagramGeneratedSite> GeneratedSites;

private:
    /*
    *  Original points added by the user.  Ordered lexigraphically by y and then x
    */
    TArray<FVector2D> OriginalSites;

    /*
     *  Stored added points as Sites that are currently being processed.  Ordered lexigraphically by y and then x
     */
    TArray<TSharedPtr<class FVoronoiDiagramSite, ESPMode::ThreadSafe>> Sites;

    /*
     *  Stores the bottom most site when running GenerateEdges
     */
    TSharedPtr<class FVoronoiDiagramSite, ESPMode::ThreadSafe> BottomMostSite;

    /*
     *  Stores the current site index when running GenerateEdges
     */
    int32 CurrentSiteIndex;

    /*
     *  Stores the minimum values of the points in site array.  Declared as pointer because these values need to be shared between some data structures.
     */
    TSharedPtr<FVector2D, ESPMode::ThreadSafe> MinValues;

    /*
     *  Stores the maximum values of the points in the site array.  Declared as pointer because these values need to be shared between some data structures.
     */
    TSharedPtr<FVector2D, ESPMode::ThreadSafe> MaxValues;

    /*
     *  Stores the delta values of the minimum and maximum values. Declared as pointer because these values need to be shared between some data structures.
     */
    TSharedPtr<FVector2D, ESPMode::ThreadSafe> DeltaValues;

    /*
     *	Sorts sites and calculates MinValues, MaxValues, and DeltaValues
     */
    void SortSitesAndSetValues();

    /*
     *  Returns the next site and increments CurrentSiteIndex
     */
    TSharedPtr<class FVoronoiDiagramSite, ESPMode::ThreadSafe> GetNextSite();

    /*
     *  Returns the left region in relation to a half edge
     */
    TSharedPtr<class FVoronoiDiagramSite, ESPMode::ThreadSafe> GetLeftRegion(TSharedPtr<class FVoronoiDiagramHalfEdge, ESPMode::ThreadSafe> HalfEdge);

    /*
     *  Returns the right region in relation to a half edge
     */
    TSharedPtr<class FVoronoiDiagramSite, ESPMode::ThreadSafe> GetRightRegion(TSharedPtr<class FVoronoiDiagramHalfEdge, ESPMode::ThreadSafe> HalfEdge);

    friend class FVoronoiDiagramHelper;
};

class FVoronoiDiagramHelper
{
public:

    /*
    * Creates an array of colors of the Voronoi Diagram to the supplied TArray<FColor>.  Assumes that diagram has been run through GenerateDiagram
    * This can be safely called from a thread
    */
    static void GenerateColorArray(TSharedPtr<FVoronoiDiagram> VoronoiDiagram, TArray<FColor>& ColorData);

    /*
     *  Creates a texture images of the Voronoi Diagram in the passed texture.  Assumes that diagram has been run through GenerateDiagram
     *  This has to be called from the game thread
     */
    static void GenerateTexture(TSharedPtr<FVoronoiDiagram> VoronoiDiagram, class UTexture2D*& GeneratedTexture);

    /*
     * Creates a PNG file of the Voronoi Diagram to the supplied TArray<uint8>.  Assumes that diagram has been run through GenerateDiagram
     * This has to be called from the game thread
     */
    static void GeneratePNG(TSharedPtr<FVoronoiDiagram> VoronoiDiagram, TArray<uint8>& PNGData);

    /*
     *  Does the passed in point lie inside of the vertices passed in.  The verices are assumed to be sorted.
     */
    static bool PointInVertices(FIntPoint Point, TArray<FVector2D> Vertices);

private:
    struct FLineSegment
    {
        FLineSegment(float InY, float InXl, float InXr, float InDy)
            : y(InY)
            , xl(InXl)
            , xr(InXr)
            , dy(InDy)
        {}

        float y, xl, xr, dy;
    };
};

class RegionDivision_VoronoiDiagram : public MapConstructorRegionDivision
{
public:
    RegionDivision_VoronoiDiagram(FIntRect InBounds);

private:
    TSharedPtr<FVoronoiDiagram> m_VoronoDiagram;
};